const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
const { Server } = require("socket.io");
const io = new Server(server);

app.use('/css', express.static('./'));
// Port
server.listen(3000, () => {
  console.log('listening on port:3000');
});

// HTML Console Page
app.get('/', (req, res) => {
  res.sendFile(__dirname + '/index.html');
});
app.get('/index.css', function(req, res) {
  res.sendFile(__dirname + "/index.css");
});

// Global variable
let rooms = [];
let clients = [];

// Helper functions
const create_user = (username, socketid) => {
  const newUser = {
    name: username,
    id: socketid,
    counter: 5,
    room: "",
  }

  clients.push(newUser);

  console.log("\nCreate User\nNew Clients List : \n");
  console.log(clients);
  return "0";
}

const create_room = (roomInput) => {
  // name = "ROOM_NAME;HOST_NAME"
  // input = ['ROOM_NAME', 'HOST_NAME']
  const [roomName, hostname] = roomInput.split(';');
  const newRoom = {
    name: roomName,
    players: [],
    host: hostname, 
    status: 0,
  }

  rooms.push(newRoom);
  console.log("\nCreate room\nNew Rooms List : \n");
  console.log(rooms);
  return "0";
}

const join_room = (roomInput) => {
  // name = "ROOM_NAME;PLAYER_NAME"
  const [roomName, playerName] = roomInput.split(";");
  // Change room ppt of player
  clients.find(el => el.name === playerName).room = roomName;
  
  // Push player in player ppt of room
  if (rooms.find(el => el.name === roomName) === undefined) {
    return "-2";
  }
  rooms.find(el => el.name === roomName).players.push(playerName);
  
  console.log("\nJoin room\nNew room list : \n");
  console.log(rooms);
  return "0";
}

const getClient = (socketid) => {
  const client = clients.find(el => el.id === socketid);
  return client;
}

const getHostName = (socketid) => {
  const client = getClient(socketid);
  const hostname = rooms.find(el => el.name === client.room).host;

  return hostname;
}

const getHost = socketid => {
  const client = getClient(socketid);
  const hostname = rooms.find(el => el.name === client.room).host;
  const host = clients.find(el => el.name === hostname);

  return host;
}

const getPlayerByName = name => {
  return (clients.find(el => el.name === name));
}

const getRoomName = socketid => {
  const client = clients.find(el => el.id === socketid);
  return client.room;
}

// Heartbeat
setInterval(() => {
    if (clients.length > 0) {
      clients.forEach(el => el.counter--);
      clientsToDC = clients.filter(el => el.counter <= 0);
      clientsToDC.forEach(el => io.in(el.id).disconnectSockets())
      clients = clients.filter(el => el.counter > 0);
      console.log(clients);
      console.log(rooms);
    }
}, 2000)

io.on('connection', (socket) => {
  console.log('a user connected');

  socket.on('req_create_user', (username) => {
    socket.emit("ack_create_user", create_user(username, socket.id));
  })

  socket.on('req_create_room', (roomInput) => {
    socket.emit("ack_create_room", create_room(roomInput));
    socket.join(roomInput.split(";")[0]);
  })

  socket.on('req_join_room', (roomInput) => {
    const roomName = roomInput.split(";")[0]
    socket.emit("ack_join_room", join_room(roomInput));
    const hostname = rooms.find(el => el.name === roomName).host;
    const hostId = clients.find(el => el.name === hostname).id;
    const playerName = clients.find(el => el.id === socket.id).name;
    io.to(hostId).emit("ack_join_room", playerName);
    
  })

  socket.on('req_rooms', () => {
    socket.emit('ack_rooms', rooms);
  })
  socket.on('req_clients', () => {
    socket.emit('ack_clients', clients);
  })

  socket.on('req_net_cmd', (cmd) => {
    io.to(getHost(socket.id).id).emit('req_net_cmd', cmd);
  })

  socket.on('ack_net_cmd', cmd => {
    console.log(cmd);
    const roomName = cmd.split("::")[0];
    arrayToParse = clients.filter(el => el.room === roomName);
    arrayToParse.forEach(el => {
      io.to(el.id).emit('ack_net_cmd', cmd.split("::")[1]);
    })

  })

  socket.on('heartbeat', name => {
    const client = getClient(socket.id);
    if (client != undefined) {
      client.counter++;
    }
    if (name === 'dashboard') {
      socket.emit("ack_rooms", rooms);
      socket.emit("ack_clients", clients);
    }
  })

  socket.on('req_start_game', (roomName) => {
    const room = rooms.find(el => el.name === roomName);
    if (room.players[0] && room.players[1]) {
      io.to(getPlayerByName(room.players[0]).id).emit("ack_start_game", "PLAYER_1");
      io.to(getPlayerByName(room.players[1]).id).emit("ack_start_game", "PLAYER_2");
      io.to(socket.id).emit("ack_start_game", room.players[0] + ";" + room.players[1]);
    }
    room.status = -1;
  })

  socket.on('req_victory', input => {
    const [roomName, playerInput] = input.split(';');
    const room = rooms.find(el => el.name === roomName);
    let victoriousPlayer = "";
    if (playerInput === 'PLAYER_1') {
      // victoriousPlayer = room.players[0];
      room.status = 1;
    } else {
      // victoriousPlayer = room.players[1];
      room.status = 2;
    }
    // io.to(getPlayerByName(room.players[0]).id).emit("ack_victory", victoriousPlayer);
    // io.to(getPlayerByName(room.players[1]).id).emit("ack_victory", victoriousPlayer);
    socket.emit('ack_victory', victoriousPlayer)
  })

  socket.on('disconnect', socket => {
    clients = clients.filter(el => el != socket.id);
    // const clientName = getClient(socket.id).name;
    // if (rooms.find(el => el.host = clientName) != undefined) {
    //   rooms.filter(el => el.host != clientName);
    // }
    console.log('A user disconnected');
  })
});


