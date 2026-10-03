// Checks the contents of the parsed WOML documents, not just that parsing succeeds

#include <regression/tframe.h>

#include "AbstractLineObject.h"
#include "FeatureVisitor.h"
#include "MeteorologicalAnalysis.h"
#include "Parser.h"
#include "Weather.h"
#include <cmath>
#include <filesystem>
#include <map>
#include <string>

using namespace std;

namespace
{
std::filesystem::path inputdir = "input";

// Counts the parsed features by type and remembers the first cold front

class Counter : public woml::FeatureVisitor
{
 public:
  std::map<std::string, int> counts;
  const woml::ColdFront* coldfront = nullptr;

#define COUNT(TYPE) \
  void visit(const woml::TYPE& /* theFeature */) override { ++counts[#TYPE]; }

  COUNT(ColdAdvection)
  COUNT(JetStream)
  COUNT(OccludedFront)
  COUNT(Ridge)
  COUNT(Trough)
  COUNT(UpperTrough)
  COUNT(WarmAdvection)
  COUNT(WarmFront)
  COUNT(AntiCyclone)
  COUNT(Antimesocyclone)
  COUNT(Cyclone)
  COUNT(HighPressureCenter)
  COUNT(LowPressureCenter)
  COUNT(Mesocyclone)
  COUNT(Mesolow)
  COUNT(ParameterValueSetPoint)
  COUNT(PointMeteorologicalSymbol)
  COUNT(PolarCyclone)
  COUNT(PolarLow)
  COUNT(TropicalCyclone)
  COUNT(ConvectiveStorm)
  COUNT(Storm)
  COUNT(CloudArea)
  COUNT(SurfacePrecipitationArea)
  COUNT(ParameterValueSetArea)
  COUNT(InfoText)
  COUNT(CloudLayers)
  COUNT(Contrails)
  COUNT(Icing)
  COUNT(Turbulence)
  COUNT(MigratoryBirds)
  COUNT(SurfaceVisibility)
  COUNT(SurfaceWeather)
  COUNT(Winds)
  COUNT(ZeroTolerance)
#undef COUNT

  void visit(const woml::ColdFront& theFeature) override
  {
    ++counts["ColdFront"];
    if (coldfront == nullptr)
      coldfront = &theFeature;
  }
};

std::string describe(const std::map<std::string, int>& counts)
{
  std::string ret;
  for (const auto& item : counts)
    ret += item.first + "=" + std::to_string(item.second) + " ";
  return ret;
}

// Parse the file and check that it contains exactly the expected features

void check(const std::string& file, std::map<std::string, int> expected)
{
  // An analysis always contains the short and long info texts, even if they are empty, so that
  // frontier overwrites the template placeholders for them
  expected["InfoText"] = 2;

  woml::Weather weather = woml::parse(inputdir / file, woml::conceptualmodelanalysis);
  if (!weather.hasAnalysis())
    throw std::runtime_error(file + ": no analysis");

  Counter counter;
  for (const auto& feature : weather.analysis())
    feature.visit(counter);

  if (counter.counts != expected)
    throw std::runtime_error(file + ": expected " + describe(expected) + "but got " +
                             describe(counter.counts));
}

}  // namespace

namespace WomlContentTest
{
void feature_types()
{
  try
  {
    check("empty.xml", {});
    check("warmfront.xml", {{"WarmFront", 1}});
    check("warmfronts.xml", {{"WarmFront", 2}});
    check("coldfront.xml", {{"ColdFront", 1}});
    check("coldandwarmfront.xml", {{"ColdFront", 1}, {"WarmFront", 1}});
    check("occlusion.xml", {{"OccludedFront", 1}});
    check("trough.xml", {{"Trough", 1}});
    check("uppertrough.xml", {{"UpperTrough", 1}});
    check("jet.xml", {{"JetStream", 1}});
    check("rain.xml", {{"SurfacePrecipitationArea", 1}});
    check("heavyrain.xml", {{"SurfacePrecipitationArea", 1}});
    check("snow.xml", {{"SurfacePrecipitationArea", 1}});
  }
  catch (std::exception& e)
  {
    TEST_FAILED(e.what());
  }
  TEST_PASSED();
}

void front_geometry()
{
  woml::Weather weather = woml::parse(inputdir / "coldfront.xml", woml::conceptualmodelanalysis);

  Counter counter;
  for (const auto& feature : weather.analysis())
    feature.visit(counter);

  if (counter.coldfront == nullptr)
    TEST_FAILED("No cold front found");

  const auto& curve = counter.coldfront->controlCurve();

  // The parser ignores the Bezier segments for now and stores the 76 point line string as the
  // only segment of the curve
  int segments = 0;
  for (const auto& segment : curve)
  {
    ++segments;
    if (segment.size() != 76)
      TEST_FAILED("The segment should have 76 points, got " + std::to_string(segment.size()));
  }
  if (segments != 1)
    TEST_FAILED("Expected 1 segment, got " + std::to_string(segments));

  // EPSG:4326 positions are in latitude,longitude order: "64.58902030964445 12.294776247655705"
  const auto& first = (*curve.begin())[0];
  if (std::abs(first.lon() - 12.294776247655705) > 1e-9 ||
      std::abs(first.lat() - 64.58902030964445) > 1e-9)
    TEST_FAILED("First point should be lon=12.2948 lat=64.5890, got lon=" +
                std::to_string(first.lon()) + " lat=" + std::to_string(first.lat()));

  // The line string approximation has 76 points
  if (curve.lineString().size() != 76)
    TEST_FAILED("Line string should have 76 points, got " +
                std::to_string(curve.lineString().size()));

  TEST_PASSED();
}

void unknown_feature()
{
  // Strict mode rejects unknown features, non-strict mode skips them
  bool failed = false;
  try
  {
    woml::parse(inputdir / "unknownobject.xml", woml::conceptualmodelanalysis);
  }
  catch (...)
  {
    failed = true;
  }
  if (!failed)
    TEST_FAILED("Strict parsing should reject an unknown feature");

  woml::Weather weather =
      woml::parse(inputdir / "unknownobject.xml", woml::conceptualmodelanalysis, false);
  Counter counter;
  for (const auto& feature : weather.analysis())
    feature.visit(counter);
  if (counter.counts != std::map<std::string, int>{{"InfoText", 2}})
    TEST_FAILED("Unknown features should be skipped, got " + describe(counter.counts));

  TEST_PASSED();
}

class tests : public tframe::tests
{
  const char* error_message_prefix() const override { return "\n\t"; }
  void test() override
  {
    TEST(feature_types);
    TEST(front_geometry);
    TEST(unknown_feature);
  }
};

}  // namespace WomlContentTest

int main()
{
  cout << endl << "WOML content tester" << endl << "===================" << endl;
  WomlContentTest::tests t;
  return t.run();
}
