#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>

#include "../../src/client/client.h"
#include "../../src/shared/state.h"

using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestWorldHandler)
{
  {
    WorldHandler::Initialize();
    BOOST_CHECK_EQUAL(WorldHandler::Turn, 0);
    WorldHandler::Turn +=10;
    BOOST_CHECK_EQUAL(WorldHandler::Turn, 10);
  }

  {
    
  }
}

/* vim: set sw=2 sts=2 et : */
