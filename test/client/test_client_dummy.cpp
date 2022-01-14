
#include <boost/test/unit_test.hpp>

#include <SFML/Graphics.hpp>
#include"../../src/client/render.h"

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestSFML)
{
  {
    //::sf::Texture texture;
    //BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int> {});
  }
}
BOOST_AUTO_TEST_CASE(TestRender){
  /*Test render*/
  render::MainFrame Mf("Mf",20, 30);
  BOOST_CHECK_EQUAL(Mf.Name(),"Mf");
  BOOST_CHECK_EQUAL(Mf.Height(),20);
  BOOST_CHECK_EQUAL(Mf.Width(),30);
  //render::MainFrame::InitActors();


}

/* vim: set sw=2 sts=2 et : */
