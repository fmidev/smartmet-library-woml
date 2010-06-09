#include <regression/tframe.h>

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

namespace WomlTest
{
  void empty()
  {
	woml::Weather weather = woml::parse(inputdir / "empty.xml");
	TEST_PASSED();
  }

  void warmfront()
  {
	woml::Weather weather = woml::parse(inputdir / "warmfront.xml");
	TEST_PASSED();
  }

  void coldfront()
  {
	woml::Weather weather = woml::parse(inputdir / "coldfront.xml");
	TEST_PASSED();
  }

  void coldandwarmfront()
  {
	woml::Weather weather = woml::parse(inputdir / "coldandwarmfront.xml");
	TEST_PASSED();
  }

  void warmfronts()
  {
	woml::Weather weather = woml::parse(inputdir / "warmfronts.xml");
	TEST_PASSED();
  }

  void signs()
  {
	woml::Weather weather = woml::parse(inputdir / "signs.xml");
	TEST_PASSED();
  }

  void cloud()
  {
	woml::Weather weather = woml::parse(inputdir / "cloud.xml");
	TEST_PASSED();
  }

  void jet()
  {
	woml::Weather weather = woml::parse(inputdir / "jet.xml");
	TEST_PASSED();
  }

  void occlusion()
  {
	woml::Weather weather = woml::parse(inputdir / "occlusion.xml");
	TEST_PASSED();
  }

  void trough()
  {
	woml::Weather weather = woml::parse(inputdir / "trough.xml");
	TEST_PASSED();
  }

  void uppertrough()
  {
	woml::Weather weather = woml::parse(inputdir / "uppertrough.xml");
	TEST_PASSED();
  }

  void rain()
  {
	// woml::Weather weather = woml::parse(inputdir / "rain.xml");
	// TEST_PASSED();
	TEST_NOT_IMPLEMENTED();
  }

  void heavyrain()
  {
	// woml::Weather weather = woml::parse(inputdir / "heavyrain.xml");
	// TEST_PASSED();
	TEST_NOT_IMPLEMENTED();
  }

  void snow()
  {
	// woml::Weather weather = woml::parse(inputdir / "snow.xml");
	// TEST_PASSED();
	TEST_NOT_IMPLEMENTED();
  }

  void value()
  {
	woml::Weather weather = woml::parse(inputdir / "value.xml");
	TEST_PASSED();
  }

  void values()
  {
	woml::Weather weather = woml::parse(inputdir / "values.xml");
	TEST_PASSED();
  }

  void pointnote()
  {
	// woml::Weather weather = woml::parse(inputdir / "pointnote.xml");
	// TEST_PASSED();
	TEST_NOT_IMPLEMENTED();
  }

  void graphic()
  {
	woml::Weather weather = woml::parse(inputdir / "graphic.xml");
	TEST_PASSED();
  }

  //! The actual test driver
  class tests : public tframe::tests
  {
	//! Overridden message separator
	virtual const char * const error_message_prefix() const
	{
	  return "\n\t";
	}

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
	  TEST(signs);
	  TEST(cloud);
	  TEST(trough);
	  TEST(uppertrough);
	  TEST(snow);
	  TEST(rain);
	  TEST(heavyrain);
	  TEST(value);
	  TEST(values);
	  TEST(pointnote);
	  TEST(graphic);
	}

  }; // class tests

} // namespace WomlTest


int main(void)
{
  cout << endl
	   << "Testing WOML serialization" << endl
	   << "==========================" << endl;
  WomlTest::tests t;
  return t.run();
}
