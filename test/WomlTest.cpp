#include <regression/tframe.h>

#include "Weather.h"
#include "Parser.h"
#include <boost/filesystem.hpp>

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
using namespace boost::filesystem;

path inputdir = "input";
path outputdir = "results";
path resultsdir = "results_ok";

struct indent
{
  int depth_;
  indent(int depth) : depth_(depth){};
};

std::ostream& operator<<(std::ostream& o, indent const& in)
{
  for (int i = 0; i != in.depth_; ++i)
  {
    o << "  ";
  }
  return o;
}

namespace WomlTest
{
void empty()
{
  woml::Weather weather = woml::parse(inputdir / "empty.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void warmfront()
{
  woml::Weather weather = woml::parse(inputdir / "warmfront.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void coldfront()
{
  woml::Weather weather = woml::parse(inputdir / "coldfront.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void coldandwarmfront()
{
  woml::Weather weather =
      woml::parse(inputdir / "coldandwarmfront.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void warmfronts()
{
  woml::Weather weather = woml::parse(inputdir / "warmfronts.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

// void signs()
//{
//	woml::Weather weather = woml::parse(inputdir / "signs.xml",woml::conceptualmodelanalysis);
//	TEST_PASSED();
//}

// void cloud()
//{
//	woml::Weather weather = woml::parse(inputdir / "cloud.xml",woml::conceptualmodelanalysis);
//	TEST_PASSED();
//}

void jet()
{
  woml::Weather weather = woml::parse(inputdir / "jet.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void occlusion()
{
  woml::Weather weather = woml::parse(inputdir / "occlusion.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void trough()
{
  woml::Weather weather = woml::parse(inputdir / "trough.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void uppertrough()
{
  woml::Weather weather = woml::parse(inputdir / "uppertrough.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void rain()
{
  woml::Weather weather = woml::parse(inputdir / "rain.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void heavyrain()
{
  woml::Weather weather = woml::parse(inputdir / "heavyrain.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void snow()
{
  woml::Weather weather = woml::parse(inputdir / "snow.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void value()
{
  woml::Weather weather = woml::parse(inputdir / "value.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

void values()
{
  woml::Weather weather = woml::parse(inputdir / "values.xml", woml::conceptualmodelanalysis);
  TEST_PASSED();
}

//  void text()
//  {
//  woml::Weather weather = woml::parse(inputdir / "text.xml",woml::conceptualmodelanalysis);
//  TEST_PASSED();
//  }

//  void graphic()
//  {
//	woml::Weather weather = woml::parse(inputdir / "graphic.xml",woml::conceptualmodelanalysis);
//	TEST_PASSED();
//  }

//  void suomitv()
//  {
//	woml::Weather weather = woml::parse(inputdir / "suomitv.xml",woml::conceptualmodelanalysis);
//	TEST_PASSED();
//  }

//! The actual test driver
class tests : public tframe::tests
{
  //! Overridden message separator
  virtual const char* error_message_prefix() const { return "\n\t"; }
  //! Main test suite
  void test(void)
  {
    TEST(empty);
    TEST(warmfront);
    TEST(coldfront);
    TEST(occlusion);
    TEST(coldandwarmfront);
    TEST(jet);
    TEST(warmfronts);
    //	  TEST(signs);
    //	  TEST(cloud);
    TEST(trough);
    TEST(uppertrough);
    TEST(snow);
    TEST(rain);
    TEST(heavyrain);
    TEST(value);
    TEST(values);
    //	  TEST(text);
    //	  TEST(graphic);
    //	  TEST(suomitv);
  }

};  // class tests

}  // namespace WomlTest

int main(void)
{
  cout << endl << "Testing WOML serialization" << endl << "==========================" << endl;
  WomlTest::tests t;
  return t.run();
}
