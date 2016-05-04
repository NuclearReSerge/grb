#include "Analyzer/GreatCircleDistance.h"

#include "test/Mock/CoordinatesMock.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

namespace
{

struct Point
{
  type::Float lambda; // longnitude
  type::Float phi;    // latitude
};

struct Distance
{
  type::Float spherical;
  type::Float haversine;
  type::Float vincenty;
};

struct TestData
{
  Point point1;
  Point point2;
  Distance result;
};

}


class GreatCircleDistanceTest : public Test
{
protected:
  void SetUp()
  { }

  void TearDown()
  { }
};

TEST_F(GreatCircleDistanceTest, defaultPoints_SphericalLawFormula)
{
  GreatCircleDistance distance(type::SPHERICAL_LAW_OF_COSINES);
  CoordinatesMock P1, P2;

  EXPECT_DOUBLE_EQ((type::Float) 0.0, distance(P1, P2));
}

TEST_F(GreatCircleDistanceTest, defaultPoints_HaversineFormula)
{
  GreatCircleDistance distance(type::HAVERSINE_FORMULA);
  CoordinatesMock P1, P2;

  EXPECT_DOUBLE_EQ((type::Float) 0.0, distance(P1, P2));
}

TEST_F(GreatCircleDistanceTest, defaultPoints_VincentyFormula)
{
  GreatCircleDistance distance(type::VINCENTY_FORMULAE);
  CoordinatesMock P1, P2;

  EXPECT_DOUBLE_EQ((type::Float) 0.0, distance(P1, P2));
}

TEST_F(GreatCircleDistanceTest, defaultPoints_UnknownFormula)
{
  GreatCircleDistance distance(type::UNKNOWN_ARC_FORMULA_TYPE);
  CoordinatesMock P1, P2;

  EXPECT_DOUBLE_EQ((type::Float) 0.0, distance(P1, P2));
}

TEST_F(GreatCircleDistanceTest, points_RandomCoordinates)
{
  GreatCircleDistance distSpherical(type::SPHERICAL_LAW_OF_COSINES);
  GreatCircleDistance distHaversine(type::HAVERSINE_FORMULA);
  GreatCircleDistance distVincenty(type::VINCENTY_FORMULAE);

  CoordinatesMock P1(type::GALACTIC);
  CoordinatesMock P2(type::GALACTIC);

  std::vector<TestData> testData
  {
    {
      1.9104897572082946, 0.049141281279405424,
      4.9294406091771075, 1.3690814096068573,
      1.7218494469382168, 1.721849446938217, 1.7218494469382168
    },
    {
      6.019872173108656, -0.8535822397786771,
      0.5419054621713149, -1.2935671389550163,
      0.555717295340718, 0.5557172953407182, 0.5557172953407182
    },
    {
      0.07080196559265672, 1.3279216182973568,
      4.119059910193305, 1.357271577511586,
      0.40981269856075986, 0.40981269856075975, 0.4098126985607598
    }
  };

  for (const TestData& data : testData)
  {
    P1.getHorizontal() = data.point1.lambda;
    P1.getVertical()   = data.point1.phi;
    P2.getHorizontal() = data.point2.lambda;
    P2.getVertical()   = data.point2.phi;
    EXPECT_DOUBLE_EQ((type::Float) data.result.spherical, distSpherical(P1, P2));
    EXPECT_DOUBLE_EQ((type::Float) data.result.haversine, distHaversine(P1, P2));
    EXPECT_DOUBLE_EQ((type::Float) data.result.vincenty,  distVincenty(P1, P2));
  }
}

}
}
