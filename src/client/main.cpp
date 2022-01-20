#include <iostream>
#include <client.h>
#include "engine.h"
#include "client/Macro.hpp"
#include "render.h"
#include "ai.h"
#include "state.h"
#include <string.h>
#include <unistd.h>
#include "../../extern/jsoncpp-1.8.0/json/json.h"
#include "../../extern/jsoncpp-1.8.0/json/json-forwards.h"
#include "../../extern/jsoncpp-1.8.0/jsoncpp.cpp"
#include <fstream>
#include <thread>
#include <sio_client.h>


// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void foo(void* param){
  printf("Test function foo\n");
  printf("l'adresse est:%p\n",param);
  printf("la valeur est:%d\n",&param);
}

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

//#include <state.h>

using namespace std;
using namespace sio;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;

sio::client io;


int main(int argc,char* argv[])
{

    cout << "Hello" << endl;
    if(argc < 1)
        cout << "No args. Exit" << endl;

    if(!strcmp(argv[1],"state"))
    {
        cout << "Begin State Unit Tests" << endl;
        system("make test");
    }
    if(!strcmp(argv[1],"render"))
    {
        MainFrame* mf = MainFrame::FromLaunchArgs("src/client/tables/LaunchArgs.csv");
        cout << "RENDER" << endl;
        FileHandler::DeserializeTable<Manager>("src/client/tables/Managers.csv","CSV");
        for(Manager* m : Manager::Managers)
            cout << m->Name() << endl;
        Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("src/client/tables/ManageablesVisuals.csv","CSV"));

        
        mf->Start();
        
    }
    if(!strcmp(argv[1],"engine"))
    {
        cout << "ENGINE : "<< getpid() << endl;
        MainFrame* mf = MainFrame::FromLaunchArgs("src/client/tables/LaunchArgs.csv");
        FileHandler::DeserializeTable<Manager>("src/client/tables/Managers.csv","CSV");
        for(Manager* m : Manager::Managers)
            cout << m->Name() << endl;
        Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("src/client/tables/ManageablesVisuals.csv","CSV"));
        mf->Start();
    }

    if(!strcmp(argv[1],"random_ai"))
    {
        cout << "RANDOM AI : "<< getpid() << endl;
        MainFrame* mf = MainFrame::FromLaunchArgs("src/client/tables/LaunchArgs.csv");
        FileHandler::DeserializeTable<Manager>("src/client/tables/Managers.csv","CSV");
        for(Manager* m : Manager::Managers)
            cout << m->Name() << endl;
        Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("src/client/tables/ManageablesVisuals.csv","CSV"));
        mf->Start();
    } 

    if(!strcmp(argv[1],"heuristic_ai"))
    {
        cout << "HEURISTIC AI : "<< getpid() << endl;
        MainFrame* mf = MainFrame::FromLaunchArgs("src/client/tables/LaunchArgs.csv");
        FileHandler::DeserializeTable<Manager>("src/client/tables/Managers.csv","CSV");
        for(Manager* m : Manager::Managers)
            cout << m->Name() << endl;
        Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("src/client/tables/ManageablesVisuals.csv","CSV"));
        mf->Start();
        WorldHandler::OnTurnBegin();
    }

    if(!strcmp(argv[1],"PROTOTYPE"))
    {
        cout << argv[2] << endl;
        io.connect(string(argv[2]) + ":3000");
        NetMessageHandler::UserName = "FortuneSeeker";
        io.set_open_listener([&]() 
        {

            NetMessageHandler::IO = &io;
            io.socket()->emit("req_create_user",NetMessageHandler::UserName );
            thread t(NetMessageHandler::KeepAlive);
            t.detach();
            io.socket()->emit("req_join_room",string("BackRoom;")+NetMessageHandler::UserName);
            io.socket()->on("ack_net_cmd",[&] (sio::event& ev)
            {
                cout << "ACK_NET_CMD : " << ev.get_message()->get_string() << endl;
            });
            io.socket()->on("ack_start_game",[&] (sio::event& ev)
            {
                
                MainFrame* mf = MainFrame::FromLaunchArgs("src/client/tables/LaunchArgs.csv");
                FileHandler::DeserializeTable<Manager>("src/client/tables/Managers.csv","CSV");
                for(Manager* m : Manager::Managers)
                    cout << m->Name() << endl;
                Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("src/client/tables/ManageablesVisuals.csv","CSV"));
                PRINTLN("ASSIGNING PLAYER");
                WorldHandler::Players = vector<Player*>();
                if(ev.get_message()->get_string() == "PLAYER_1")
                {
                    WorldHandler::Players.push_back(new Player("PLAYER_1",1,NULL));
                    WorldHandler::Players.push_back(new Player("PLAYER_2",0,NULL));
                    WorldHandler::MyID = 1;
                    cout << "I AM 1 " << ev.get_message()->get_string() << endl;

                } 
                else if(ev.get_message()->get_string() == "PLAYER_2")
                {
                    WorldHandler::Players.push_back(new Player("PLAYER_2",0,NULL));
                    WorldHandler::Players.push_back(new Player("PLAYER_1",1,NULL));
                    WorldHandler::MyID = 0;
                    cout << "I AM 2 " << ev.get_message()->get_string() << endl;

                } 
                mf->WakeUp();
                PRINTLN("WAKE UP OK");
                WorldHandler::GetMyPlayer()->Behaviour(Script::Scripts["MNK"]);
                for(Player* p : WorldHandler::Players)
                {
                    if(p->Behaviour())
                    {
                        p->Behaviour()->INT("PlayerID",(int)p->ID());
                        p->Behaviour()->STRING("PlayerName",p->Name());
                    }
                }
                PRINTLN("SCRIPT OK");
                WorldHandler::CurrentWorld->Behaviour()->Run();
                PRINTLN("WH BHV OK");
                mf->Start();
            });
            
            cout << "CONNECTED" << endl;
        });  

        while(1) usleep(500000);
    }
    if(!strcmp(argv[1],"TREE"))
    {
        MainFrame* mf = MainFrame::FromLaunchArgs("src/client/tables/LaunchArgs.csv");
        FileHandler::DeserializeTable<Manager>("src/client/tables/Managers.csv","CSV");
        for(Manager* m : Manager::Managers)
            cout << m->Name() << endl;
        Manager::GetMgrByID(0)->Elements(FileHandler::DeserializeTable<Manageable>("src/client/tables/ManageablesVisuals.csv","CSV"));
        InputHandler::Initialize();
        WorldHandler::Initialize();
        SelectionHandler::Selection = std::vector<state::Manageable**>();
        mf->InitWorld();
        mf->InitActors();

        Actor* actor = (Actor*)Manager::GetMgrByID(3)->GetByName("cyan_bowman").front();
        std::vector<Actor*> enemies;
        enemies.push_back((Actor*)Manager::GetMgrByID(3)->GetByName("red_knight").front());
        enemies.push_back((Actor*)Manager::GetMgrByID(3)->GetByName("red_mage").front());
        enemies.push_back((Actor*)Manager::GetMgrByID(3)->GetByName("red_dragon").front());
        enemies[0]->AssignPosition(actor->Position().x,actor->Position().y + 2);    
        std::vector<Node*> aleaf;
        std::vector<Node*> bhvleaves;
        std::vector<Node*> en_bhvleaves;
        std::vector<Node*> enemy_aleaf;
        std::vector<std::vector<Node*>> aleaves;
        std::vector<std::vector<Node*>> leaves;
        BehaviourTree* bhv_tree = WorldHandler::Behaviour->BHV_TREES["actor_bhv"];
        bhv_tree->Caster = actor;
        bhv_tree->Root = new Node(new BehaviourLeaf(actor,NULL,"ROOT"));
        PRINTLN(bhv_tree->Caster->Name());

        PARSE_MAP(bhv_tree->Inputs,std::string,std::string,
        
            bhvleaves.push_back(new Node(new BehaviourLeaf(actor,NULL,it->first)));

        )

        for(Actor* en : enemies)
        {
            PARSE_MAP(bhv_tree->Inputs,std::string,std::string,
        
            en_bhvleaves.push_back(new Node(new BehaviourLeaf(en,NULL,it->first)));
        
        )
        }
        PRINTLN("MILESTONE");

        // int i = 0;
        // for(Action* action : actor->ActionList())
        //     aleaf.push_back(new Node(new ActionLeaf(action->Name(),actor,action,aleaf.size())));
    

        // for(Actor* a : enemies)
        //     for(Action* action : a->ActionList())
        //         enemy_aleaf.push_back(new Node(new ActionLeaf(action->Name(),a,action,enemy_aleaf.size())));

        // aleaves.push_back(aleaf);
        // aleaves.push_back(enemy_aleaf); 
        leaves.push_back(bhvleaves);
        leaves.push_back(en_bhvleaves);
        
        PRINTLN(((BehaviourLeaf*)bhv_tree->Root->Object)->ToString());
        Node* root = bhv_tree->Root;
        //Node* root = new Node(new ActionLeaf("ROOT",actor,actor->ActionList()[0],0));
        
        //root->RecursiveInsert(aleaves,0);
        root->RecursiveInsertWithCallback<BehaviourTree>(leaves,0);
        root->Print(0);
        cout << "LEVEL I : " << endl;
        for(Node* n : bhv_tree->Level(2))
            cout << ((BehaviourLeaf*)n->Object)->ToString() << endl;
        cout << "END LEVEL  : " << bhv_tree->Level() << endl;
        
        Node* choice = Node::chooseAction(root);
        //cout << "APRES ALPHA-BETA : \n" << endl;
        //root->Print(0);
        //cout << "ACTION CHOISIE : \n" << endl;
        //choice->Print(0);
        /*root->BottomLevel(bhv_tree);

        root->Print(0);
        cout << "BOTTOM LEVEL" << endl;*/

            
    }
    if(!strcmp(argv[1],"Thread"))
    {
        // cout << "Test Thread\n" << endl;
        // cout<<"-------------------------------------------\n";
        // cout<<"Test param Null\n";
        // WorldHandler::RunFunctionInNewThread(foo,NULL);

        // cout<<"-------------------------------------------\n";
        // cout<<"Test les pointeurs entier\n";
        // int* p=(int*)malloc(sizeof(int));
        // *p=60;
        // WorldHandler::RunFunctionInNewThread(foo,p);

    }  
    
    if(!strcmp(argv[1],"Json"))
    {

    }
    
    return 0;
}
