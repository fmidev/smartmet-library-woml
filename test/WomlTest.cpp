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
	  TEST(coldandwarmfront);
	  TEST(warmfronts);
	  TEST(signs);
	  TEST(cloud);
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
