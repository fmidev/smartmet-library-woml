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
	TEST_NOT_IMPLEMENTED();
  }

  void warmfront()
  {
	path infile = inputdir / "warmfront.xml";
	path outfile = outputdir / "warmfront";
	path resultsfile = resultsdir / "warmfront";

	woml::Weather weather = woml::parse(infile);

	TEST_NOT_IMPLEMENTED();
  }

  void coldfront()
  {
	TEST_NOT_IMPLEMENTED();
  }

  void coldandwarmfront()
  {
	TEST_NOT_IMPLEMENTED();
  }

  void warmfronts()
  {
	TEST_NOT_IMPLEMENTED();
  }

  void signs()
  {
	TEST_NOT_IMPLEMENTED();
  }

  void cloud()
  {
	TEST_NOT_IMPLEMENTED();
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
