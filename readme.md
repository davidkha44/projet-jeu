<!--
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

# ENSEA PLT Project 2021-2022: Royal War

<p align="center">
 
  <!-- logo of the project/game here -->
  <img height="300" src="https://perso-etis.ensea.fr/neurocyber/web/images/logo_ensea.png" alt="logo"/>  

  <div align="center">

  [![c++ version][cpp-ver-shield]][cpp-ver]
  [![software version][version-shield]][cpp-ver]

  </div>
</p>

<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Game](#about-the-game)
  * [Presentation](#Presentation)
  * [Rules](#rules)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
  * [Installation](#installation)
* [Usage](#usage)
  * [Basic Testing](#basic-testing)
* [Release History](#release-history)
* [Built With](#built-with)
* [Contributing](#contributing)
* [License](#license)

<!-- Introduction -->
## Introduction

The [*PLT*] **P**rojet **L**ogiciel **T**ransversal (Transversal Software Project) is the third year project in specialization [*IS*] **I**nformatique et **S**ystèmes (computer science and system) at [ENSEA](https://www.ensea.fr/fr). 

<!-- ABOUT THE PROJECT -->
# About the game

## Presentation

* Genre : Strategy Game
* Players : 1 to 2 players

Royal War is a strategy game that can be played solo against the AI or against an opponent. 

Your main objective is to destroy your opponent base.

You have a base and several buildings where you can spawn your troops.
Each troops have their own strength and weakness, it falls to you to choose what kind of troops you want.

## Rules

### Starting

You start with a dragon, a mage, a knight, an archer and a soldier, just like your opponent.
 
### Permitted moves
* Key ``M`` : move mode for the selected character
* Key ``A`` : attack mode for the selected character
* Key ``T`` : pass your turn to your opponent

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

Resynchronize the package index files 
```sh
sudo apt-get update
```

Install with apt-get
```sh
sudo apt-get install build-essential \
dia \
libsfml-dev libxml2-dev libmicrohttpd-dev libboost-all-dev \
python3 python3-pip \
lcov gcovr
```

Install python package with pip (or pip3)
```sh
pip install gcovr
```

Install NodeJS
``sh
sudo apt install nodejs
``

Install the server dependencies
``sh
npm install express socket.io
npm install -g localtunnel
``

Install socket.io and its dependencies
1. Use `git clone --recurse-submodules https://github.com/socketio/socket.io-client-cpp.git` to clone your local repo.
2. Run `cmake  ./`
3. Run `make install`(if makefile generated) or open generated project (if project file generated) to build.
4. Outputs is under `./build`, link with the all static libs under `./build/lib` and  include headers under `./build/include` in your client code where you want to use it.
5. Install the dependencies with ``sudo apt-get install libjsoncpp-dev rapidjson-dev libasio-dev libwebsocketpp-dev catch``

### Installation

1. Clone the repo
npm install socket.ionpm install socket.io```sh
git clone https://github.com/davidkha44/projet-jeu
cd projet-jeu
```

2. Build it
```sh
projet-jeu$ make
```

<!-- USAGE -->
## Usage

## Basic Testing

Print a hello world message
```sh
projet-jeu$ bin/client hello
```

Render demo
```sh
projet-jeu$ bin/client render
```

Engine demo
```sh
projet-jeu$ bin/client engine
```
Radom AI demo
```sh
projet-jeu$ bin/client random_ai
```

Heuristic AI demo
```sh
projet-jeu$ bin/client heuristic_ai
```

Server
1. Launch the server with `node ./src/server/jsserver/index.js`
2. Run `lt --port 3000 --subdomain fredurl`
3. Launch your server with `./bin/server listen <ROOM_NAME>`
4. Join the created room with `./bin/client <ROOM_NAME>`

<!-- RELEASE HISTORY-->
## Release History

* <a href="https://github.com/davidkha44/projet-jeu/releases/tag/1.1">1.1</a>
    * Environnement de développement
    * Ressources
    * Rapport section 1 : Présentation générale
    * Code : affichage message `./bin/client hello`

* <a href="https://github.com/davidkha44/projet-jeu/releases/tag/1.final">1.final</a>
    * Rapport section 2 : Description et Conception des états
    * Code : implantation et tests unitaires états `./bin/client state`

* <a href="https://github.com/davidkha44/projet-jeu/releases/tag/2.1">2.1</a>
    * Rapport section 3 : Description et Conception du Rendu
    * Code : rendu d’un état `./bin/client render`

* <a href="https://github.com/davidkha44/projet-jeu/releases/tag/2.2">2.2</a>
    * Rapport section 4 : Règles de changement d’états et moteur de jeu
    * Code : changement d’état `./bin/client engine`

* <a href="https://github.com/davidkha44/projet-jeu/releases/tag/2.final">2.final</a>
    * Rapport section 5 : Intelligence Artificielle
    * Code : IA random

* <a href="https://github.com/davidkha44/projet-jeu/releases/tag/3.1">3.1</a>
    * Rapport section 5 : Intelligence Artificielle
    * Code : IA heuristique

* <a href="https://github.com/davidkha44/projet-jeu/releases/tag/3.final">3.final</a>
    * Rapport section 5 : Intelligence Artificielle
    * Code : IA avancée basé sur un arbre de recherche

<!-- * <a href="https://github.com/davidkha44/projet-jeu/releases/tag/4.1">4.1</a>
    * Rapport section 6 : Modularisation
    * Code : Threads `./bin/client thread`
    * Code : Enregistrer `./bin/server record`
    * Code : Rejouer `./bin/client play`

* <a href="https://github.com/davidkha44/projet-jeu/releases/tag/4.2">4.2</a>
    * Rapport section 6 : Modularisation
    * Code : Serveur `./bin/server listen`
    * Code : Client réseau `./bin/client network` -->

* <a href="https://github.com/davidkha44/projet-jeu/releases/tag/4.final">4.final</a>
    * Rapport section 6 : Modularisation

## Built With

* [SFML](https://github.com/SFML/SFML)
* [Dia Diagram Editor](http://dia-installer.de/index.html.en)
* [dia2code](http://dia2code.sourceforge.net/)
* [libxml2](http://www.xmlsoft.org/)
* [JsonCpp](https://github.com/open-source-parsers/jsoncpp)
* [Socket.io-client-cpp](https://github.com/socketio/socket.io-client-cpp)

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, 
inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->
## License

Distributed under the MIT License. See [LICENSE][license-url] for more information.

<!-- MARKDOWN LINKS & IMAGES -->

[contributors-shield]: https://img.shields.io/github/contributors/davidkha44/projet-jeu.svg?style=flat-square
[contributors-url]: https://github.com/davidkha44/projet-jeu/graphs/contributors

[forks-shield]: https://img.shields.io/github/forks/davidkha44/projet-jeu.svg?style=flat-square
[forks-url]: https://github.com/davidkha44/projet-jeu/network/members

[stars-shield]: https://img.shields.io/github/stars/davidkha44/projet-jeu.svg?style=flat-square
[stars-url]: https://github.com/davidkha44/projet-jeu/stargazers

[issues-shield]: https://img.shields.io/github/issues/davidkha44/projet-jeu.svg?style=flat-square
[issues-url]: https://github.com/davidkha44/projet-jeu/issues

[license-shield]: https://img.shields.io/github/license/davidkha44/projet-jeu.svg?style=flat-square
[license-url]: https://github.com/davidkha44/projet-jeu/blob/master/LICENSE

[cpp-ver-shield]: https://img.shields.io/badge/C%2B%2B-11-blue.svg
[cpp-ver]: https://en.wikipedia.org/wiki/C%2B%2B11

[version-shield]: https://img.shields.io/badge/version-0.0-blue.svg?cacheSeconds=2592000