
#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"

using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestExemple)
{
  {
    Element ex(0,0,0);

    BOOST_CHECK_EQUAL(ex.getX(), 0);
    ex.setX(21);
    BOOST_CHECK_EQUAL(ex.getX(), 21);
    BOOST_CHECK_EQUAL(ex.getY(), 0);
    ex.setY(40);
    BOOST_CHECK_EQUAL(ex.getY(), 40);
    BOOST_CHECK_EQUAL(ex.getTypeID(),0);
    ex.setTypeID(30);
    BOOST_CHECK_EQUAL(ex.getTypeID(),30);
  
  }

  {
    ElementTab exTab(60,50);
    BOOST_CHECK_EQUAL(exTab.getWidth(),60);
    BOOST_CHECK_EQUAL(exTab.getHeight(),50);
    exTab.resize(30,20);
    BOOST_CHECK_EQUAL(exTab.getHeight(),20);
    BOOST_CHECK_EQUAL(exTab.getWidth(),30);
    BOOST_CHECK_LE(exTab.getHeight(), 32); // Less than equal
    BOOST_CHECK_GT(exTab.getWidth(), 11); // Greater than equl
    
  }
  {
    State Sta;
    BOOST_CHECK_EQUAL(Sta.getTurn(),1);
    BOOST_CHECK(!Sta.getEnd());
    BOOST_CHECK(!Sta.getWin());
    Sta.setTurn(30);
    BOOST_CHECK_EQUAL(Sta.getTurn(),30);
    Sta.setEnd(true);
    BOOST_CHECK(Sta.getEnd());
    Sta.setWin(true);
    BOOST_CHECK(Sta.getWin());
  }
  {
    EntiteStats es;
    BOOST_CHECK_EQUAL(es.getCost(),0);
    BOOST_CHECK_EQUAL(es.getDef(),0);
    BOOST_CHECK_EQUAL(es.getDeplacement(),0);
    BOOST_CHECK_EQUAL(es.getAtk(),0);
    BOOST_CHECK_EQUAL(es.getPV(),0);
    BOOST_CHECK_EQUAL(es.getMag(),0);
    es.setAtk(60);
    es.setDef(50);
    es.setDeplacement(20);
    es.setPV(60);
    es.setMag(40);
    //es.setMoney(10);
    //BOOST_CHECK_EQUAL(es.getCost(),10);
    BOOST_CHECK_EQUAL(es.getDef(),50);
    BOOST_CHECK_EQUAL(es.getDeplacement(),20);
    BOOST_CHECK_EQUAL(es.getAtk(),60);
    BOOST_CHECK_EQUAL(es.getPV(),60);
    BOOST_CHECK_EQUAL(es.getMag(),40);
  }
  { 
    //EntiteStatusID n;
    //EntiteStatusID l; 
    //EntiteStats es;
    //Entite en(n,3,8,l,es);
  }
}

/* vim: set sw=2 sts=2 et : */
