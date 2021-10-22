#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>


#include "../../src/shared/state.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestState)
{
  BOOST_CHECK_EQUAL(WorldHandler::Turn,0);
  WorldHandler::Turn += 10;
  BOOST_CHECK_EQUAL(WorldHandler::Turn,10);

  Manageable m;
  BOOST_CHECK_EQUAL(m.ID(),0);
  BOOST_CHECK_EQUAL(m.Name(),"TEST_OBJ");
  m.Name("FRED");
  BOOST_CHECK_EQUAL(m.Name(),"FRED");


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
  BOOST_CHECK_EQUAL(actor->HP(), 0);
  actor->Name("ACTOR");
  BOOST_CHECK_EQUAL(actor->Name(),"ACTOR");
  BOOST_CHECK_EQUAL(actor->MP(), 0);
  BOOST_CHECK_EQUAL(actor->AP(), 0);
  BOOST_CHECK_EQUAL(actor->DMG(), 0);
  BOOST_CHECK_EQUAL(actor->DEF(), 0);

  Manager *manager = new Manager("Bob", 1);
  BOOST_CHECK_EQUAL(manager->Name(), "Bob");
  BOOST_CHECK_EQUAL(manager->ID(), 1);
}


/* vim: set sw=2 sts=2 et : */
