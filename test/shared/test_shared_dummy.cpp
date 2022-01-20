#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>
#include<vector>

#include "../../src/shared/state.h"
#include "../../src/client/render.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestState)
{
  /* Test class WorldHandler */
  WorldHandler::Initialize();
  BOOST_CHECK_EQUAL(WorldHandler::Turn,0);
  WorldHandler::Turn += 10;
  BOOST_CHECK_EQUAL(WorldHandler::Turn,10);
  BOOST_CHECK_EQUAL(WorldHandler::Instance,0);
  BOOST_CHECK_EQUAL(WorldHandler::Status,0);
  BOOST_CHECK(!(WorldHandler::IsOver()));
  BOOST_CHECK_EQUAL(WorldHandler::WinnerID(),-1);
  WorldHandler::Status+=100;
  WorldHandler::LoadTurn(10);
  

  /*Test Player*/
  Player *a = new Player("paul",2);
  BOOST_CHECK_EQUAL(a->Name(), "paul");
  BOOST_CHECK_EQUAL(a->ID(),2);
  a->Name("Jean");
  a->ID(35);
  BOOST_CHECK_EQUAL(a->Name(), "Jean");
  BOOST_CHECK_EQUAL(a->ID(), 35);
  Player *b=new Player();
  
  /*Tester les fonctions de WorldHandler liées aux Player*/
  WorldHandler::Players.push_back(a);
  WorldHandler::Players.push_back(b);
  WorldHandler::MyID=35;
  Player *c= WorldHandler::GetMyPlayer();
  Player *d= WorldHandler::GetPlayerByID(0);

  BOOST_CHECK_EQUAL(WorldHandler::GetPlayerByName("TEST_PLAYER")->ID(),0);
 
  


  /*Test World*/
  World w = World();
  BOOST_CHECK_EQUAL(w.Name(), "STD_WORLD");
  BOOST_CHECK_EQUAL(w.ResPath(),"STD_PATH");

  World w2 = World("Monde","zzz",1,6,4,9);
  BOOST_CHECK_EQUAL(w2.Name(), "Monde");
  BOOST_CHECK_EQUAL(w2.ResPath(),"zzz");
  BOOST_CHECK_EQUAL(w2.CellSize().x, 1);
  BOOST_CHECK_EQUAL(w2.CellSize().y, 6);

  World w3=World({"WORLD_TEST","src/client/maps/WorldTest.csv","40","40","30","19","LAYER_ACTOR"});
  w3.ApplyGridThickness(3);

  World w4=World("WORLD_RIVER,src/client/maps/WorldWithRiver.csv,40,40,30,19,LAYER_ACTO");
  
  WorldHandler::Initialize(&w3);
  

  /*Test Actor*/
  Actor *actor = new Actor();
  BOOST_CHECK_EQUAL(actor->Property("HP"), 0);
  actor->Name("ACTOR");
  BOOST_CHECK_EQUAL(actor->Name(),"ACTOR");
  BOOST_CHECK_EQUAL(actor->Property("DEF") , 0);
  BOOST_CHECK_EQUAL(actor->Property("HP"), 0);
  BOOST_CHECK_EQUAL(actor->Property("MP") , 0);
  BOOST_CHECK_EQUAL(actor->Property("AP"), 0);
  BOOST_CHECK_EQUAL(actor->Property("X"),0);
  BOOST_CHECK_EQUAL(actor->Property("Y"),0);
  actor->AssignPosition(5,6);
  BOOST_CHECK_EQUAL(actor->Property("X"),5);
  BOOST_CHECK_EQUAL(actor->Property("Y"),6);
  BOOST_CHECK_EQUAL(actor->GetNetParam("X"),5);
  BOOST_CHECK_EQUAL(actor->GetNetParam("Y"),6);
  BOOST_CHECK(!(actor->Property("render")));
  actor->AssignPosition({8,9});
  BOOST_CHECK_EQUAL(actor->GetNetParam("X"),8);
  BOOST_CHECK_EQUAL(actor->GetNetParam("Y"),9);
  actor->Property("render",true);
  BOOST_CHECK((actor->Property("render")));
  actor->Property("X",10);
  actor->Property("Y",15);
  
  actor->ChangeAction("STD_ATTACK");
  actor->Save();
  actor->ActionList();
  
  
  /*Test des fonctions de Player qui ont des relation avec des Actors*/ 
  a->AttachPawn(actor);
  //actor->OnSelectionAdd();
    
  /*Test Manager*/
  Manager *manager = new Manager("Bob", 1);
  BOOST_CHECK_EQUAL(manager->Name(), "Bob");
  BOOST_CHECK_EQUAL(manager->ID(), 1);
  BOOST_CHECK_EQUAL(Manager::GetMgrByName("Bob")->Name(),"Bob");
  BOOST_CHECK_EQUAL(Manager::GetMgrByName("Bob")->ID(),1);
  BOOST_CHECK_EQUAL(Manager::GetMgrByID(1)->ID(),1);

  Manager mg({"ACTOR_MGR","3","18"});
  Manager mg1("Mg");



  /*Test Manageablea*/
  Manageable m;
  BOOST_CHECK_EQUAL(m.ID(),0);
  BOOST_CHECK_EQUAL(m.Name(),"TEST_OBJ");
  m.Name("FRED");
  BOOST_CHECK_EQUAL(m.Name(),"FRED");
  BOOST_CHECK(!(m.Render()));
  BOOST_CHECK(!(m.Selected()));
  BOOST_CHECK_EQUAL(m.Position().x,0);
  BOOST_CHECK_EQUAL(m.Position().y,0);
  BOOST_CHECK_EQUAL(m.Scale().x,0);
  BOOST_CHECK_EQUAL(m.Scale().x,0);
  //BOOST_CHECK_EQUAL(m.ResPath(),"TEST_RESPATH");
  //Manageable *m1=new Manageable("Mana", "Bob","res/texture/");
  //Manageable m2("Mana2", 2,"TEST_RESPATH");
  m.AssignPosition(4,9);
  BOOST_CHECK_EQUAL(m.Position().x,4);
  BOOST_CHECK_EQUAL(m.Position().y,9);

  /*Manageable *m4=new Manageable({"ACTOR_REDMAGE","ASSET_MGR","1105","res/texture/Characters/Prototypes/MageRed.png","2","2"});
  Manageable *m5=new Manageable("ACTOR_CYANMAGE,ASSET_MGR,1106,res/texture/Characters/Prototypes/MageCyan.png,2,2");
  m4->OnSelectionAdd();
  m4->OnSelectionRemove();*/
  m.AssignPosition({5,10});

  //Actor act2({"HERO_REDMAGE","ACTOR_REDMAGE","100","70","35","5","3","STD_ATTACK;STD_MOVE"});


  /*vérification des fonctions de manager qui ont relation avec Manageable*/
  /*manager->Add(m5);
  manager->Remove(m5);
  manager->Add(m4);
  manager->Add(m1);*/
  manager->GetByName("ACTOR_REDMAGE");
  manager->GetByID(1105);
  manager->GetByPos(4,5);
  manager->GetByPos({4,5});
  manager->Save();
  manager->Save("res/texture");
  manager->Load("res/texture");
  manager->OnTurnBegin();
  manager->OnTurnEnd();
  

  //WorldHandler::OnTurnBegin();
  //WorldHandler::OnTurnBeginAsync();
  //WorldHandler::OnTurnEnd();
  //WorldHandler::OnTurnEndAsync;

}

BOOST_AUTO_TEST_CASE(TestEngine){
  /*Test Engine*/
  engine::Action ark({"STD_ATTACK","1000","1","0","PATTERN_DIAMOND4","NET_CMD_ATTACK","1"});
  BOOST_CHECK_EQUAL(ark.Name(),"STD_ATTACK");
  BOOST_CHECK_EQUAL(ark.OPCode(),1000);
  BOOST_CHECK_EQUAL(ark.CostAP(),1);
  BOOST_CHECK_EQUAL(ark.CostMP(),0);
  BOOST_CHECK(ark.RequireRangeCheck());
  ark.Name("STD_MOVE_TOWARD_POS");
  ark.OPCode(2020);
  ark.CostAP(0);
  ark.CostMP(1);
  engine::Pattern p1({"PATTERN_SQUARE1","src/client/actions_patterns/PatternSquare1.csv","3","3"});
  ark.BasePattern(&p1);
  engine::NetCommand cmd({"NET_CMD_MOVE_TOWARD_POS","MoveTowardPos:$X;$X;$X","caster.ID;target.X;target.Y"});
  ark.NetCmd(&cmd);
  BOOST_CHECK_NE(ark.Name(),"STD_ATTACK");
  BOOST_CHECK_EQUAL(ark.OPCode(),2020);
  BOOST_CHECK_EQUAL(ark.CostAP(),0);
  BOOST_CHECK_EQUAL(ark.CostMP(),1);
  
  engine::NetCommand ncmd({"NET_CMD_MOVE","Move:$X;$X;$X","caster.ID;target.X;target.Y"});
  BOOST_CHECK_EQUAL(ncmd.Name(),"NET_CMD_MOVE");
  BOOST_CHECK_EQUAL(ncmd.Format().first,"Move:$X;$X;$X");
  BOOST_CHECK_EQUAL(ncmd.Format().second,"caster.ID;target.X;target.Y");

  engine::Pattern p({"PATTERN_SQUARE1","src/client/actions_patterns/PatternSquare1.csv","3","3"});
  
  //BOOST_CHECK_EQUAL(ark.BasePattern(),p);
  //BOOST_CHECK_EQUAL(ark.NetCmd()->Name(),"NET_CMD_ATTACK");
  //BOOST_CHECK_EQUAL(ark.RequireRangeCheck(),false);
  //engine::Action ivk({"STD_INVOKE","3000","1","0","PATTERN_CROSS","NET_CMD_INVOKE_RED","1"});
  //Actor* act2=new Actor({"BUILDING_REDKEEP","ACTOR_REDKEEP","100","20","70","100","0","STD_INVOKE"});
  //engine::Action* a1 = engine::Action::GetByNetCmd("NET_CMD_MOVE");
  //BOOST_CHECK_EQUAL(a1->Name(),"STD_MOVE");
  
}

BOOST_AUTO_TEST_CASE(TestAi){
  int tab[2];
  tab[0]=2;
  tab[1]=3;
  int rand = ai::RandomAI::RandomInt(tab);
  BOOST_CHECK_GE(rand,2);
  BOOST_CHECK_LE(rand,3);

  int norm0 = ai::Heuristics::Norm1(-2,5);
  sf::Vector2i dir(-2,5);
  int norm1 = ai::Heuristics::Norm1(dir);
  BOOST_CHECK_EQUAL(norm0,7);
  BOOST_CHECK_EQUAL(norm1,7);
  BOOST_CHECK_EQUAL(norm0,norm1);

  int test = 10;
  void* obj = &test;
  ai::Node root = new ai::Node(obj);
  ai::Node node1 = new ai::Node(obj,&root);

  
}

/* vim: set sw=2 sts=2 et : */
