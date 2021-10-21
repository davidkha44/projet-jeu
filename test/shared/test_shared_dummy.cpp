
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
    ex.setY(21);
    BOOST_CHECK_EQUAL(ex.getY(), 21);
  }

  {
    //Element ex {};
    //ex.setX(21);
    //BOOST_CHECK_LE(ex.x, 32); // Less than equal
    //BOOST_CHECK_GT(ex.x, 11); // Greater than equl
  }
}

/* vim: set sw=2 sts=2 et : */
