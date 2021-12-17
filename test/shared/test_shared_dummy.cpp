#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>


#include "../../src/shared/state.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestState)
{
  /* Test class WorldHandler */
  BOOST_CHECK_EQUAL(WorldHandler::Turn,0);
  WorldHandler::Turn += 10;
  BOOST_CHECK_EQUAL(WorldHandler::Turn,10);


  

  /*Test Player*/
  Player *a = new Player("paul",2);
  BOOST_CHECK_EQUAL(a->Name(), "paul");
  BOOST_CHECK_EQUAL(a->ID(),2);
  a->Name("Jean");
  a->ID(35);
  BOOST_CHECK_EQUAL(a->Name(), "Jean");
  BOOST_CHECK_EQUAL(a->ID(), 35);

  World w = World();
  BOOST_CHECK_EQUAL(w.Name(), "STD_WORLD");
  BOOST_CHECK_EQUAL(w.ResPath(),"STD_PATH");
  World w2 = World("Monde","zzz",1,6,4,9);
  BOOST_CHECK_EQUAL(w2.Name(), "Monde");
  BOOST_CHECK_EQUAL(w2.ResPath(),"zzz");
  BOOST_CHECK_EQUAL(w2.CellSize().x, 1);
  BOOST_CHECK_EQUAL(w2.CellSize().y, 6);

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


  Manager *manager = new Manager("Bob", 1);
  BOOST_CHECK_EQUAL(manager->Name(), "Bob");
  BOOST_CHECK_EQUAL(manager->ID(), 1);
  BOOST_CHECK_EQUAL(Manager::GetMgrByName("Bob")->Name(),"Bob");
  BOOST_CHECK_EQUAL(Manager::GetMgrByName("Bob")->ID(),1);
  BOOST_CHECK_EQUAL(Manager::GetMgrByID(1)->ID(),1);


  /*Test classe Manageablea*/
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
  BOOST_CHECK_EQUAL(m.ResPath(),"TEST_RESPATH");
  Manageable m1("Mana", "Bob","res/texture/");
  Manageable m2("Mana2", 2,"TEST_RESPATH");
  m.AssignPosition(4,9);
  BOOST_CHECK_EQUAL(m.Position().x,4);
  BOOST_CHECK_EQUAL(m.Position().y,9);
  //BOOST_CHECK_EQUAL(manager->GetByPos(4,9)->Name(),"Fred");
  




}



/* vim: set sw=2 sts=2 et : */
