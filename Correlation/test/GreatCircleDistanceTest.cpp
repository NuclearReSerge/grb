#include "Correlation/GreatCircleDistance.h"

#include "test/Mock/CoordinatesMock.h"

#include <gtest/gtest.h>

namespace
{

struct Point
{
  grb::type::Float lambda; // longnitude
  grb::type::Float phi;    // latitude
};

struct Distance
{
  grb::type::Float spherical;
  grb::type::Float haversine;
  grb::type::Float vincenty;
};

struct TestData
{
  Point point1;
  Point point2;
  Distance result;
};

} // namespace

namespace testing
{

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
  grb::GreatCircleDistance distance(grb::type::SPHERICAL_LAW_OF_COSINES);
  grb::CoordinatesMock P1(grb::type::UNDEFINED_COORDINATE_SYSTEM, grb::type::UNDEFINED_DATE);
  grb::CoordinatesMock P2(grb::type::UNDEFINED_COORDINATE_SYSTEM, grb::type::UNDEFINED_DATE);

  EXPECT_DOUBLE_EQ((grb::type::Float) 0.0, distance(P1, P2));
}

TEST_F(GreatCircleDistanceTest, defaultPoints_HaversineFormula)
{
  grb::GreatCircleDistance distance(grb::type::HAVERSINE_FORMULA);
  grb::CoordinatesMock P1(grb::type::UNDEFINED_COORDINATE_SYSTEM, grb::type::UNDEFINED_DATE);
  grb::CoordinatesMock P2(grb::type::UNDEFINED_COORDINATE_SYSTEM, grb::type::UNDEFINED_DATE);

  EXPECT_DOUBLE_EQ((grb::type::Float) 0.0, distance(P1, P2));
}

TEST_F(GreatCircleDistanceTest, defaultPoints_VincentyFormula)
{
  grb::GreatCircleDistance distance(grb::type::VINCENTY_FORMULAE);
  grb::CoordinatesMock P1(grb::type::UNDEFINED_COORDINATE_SYSTEM, grb::type::UNDEFINED_DATE);
  grb::CoordinatesMock P2(grb::type::UNDEFINED_COORDINATE_SYSTEM, grb::type::UNDEFINED_DATE);

  EXPECT_DOUBLE_EQ((grb::type::Float) 0.0, distance(P1, P2));
}

TEST_F(GreatCircleDistanceTest, defaultPoints_UnknownFormula)
{
  grb::GreatCircleDistance distance(grb::type::UNDEFINED_ARC_FORMULA);
  grb::CoordinatesMock P1(grb::type::UNDEFINED_COORDINATE_SYSTEM, grb::type::UNDEFINED_DATE);
  grb::CoordinatesMock P2(grb::type::UNDEFINED_COORDINATE_SYSTEM, grb::type::UNDEFINED_DATE);

  EXPECT_DOUBLE_EQ((grb::type::Float) 0.0, distance(P1, P2));
}

TEST_F(GreatCircleDistanceTest, points_RandomCoordinates)
{
  grb::GreatCircleDistance distSpherical(grb::type::SPHERICAL_LAW_OF_COSINES);
  grb::GreatCircleDistance distHaversine(grb::type::HAVERSINE_FORMULA);
  grb::GreatCircleDistance distVincenty(grb::type::VINCENTY_FORMULAE);

  grb::CoordinatesMock P1(grb::type::GALACTIC, grb::type::UNDEFINED_DATE);
  grb::CoordinatesMock P2(grb::type::GALACTIC, grb::type::UNDEFINED_DATE);

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
    P1.getX2() = data.point1.lambda;
    P1.getX3() = data.point1.phi;
    P2.getX2() = data.point2.lambda;
    P2.getX3() = data.point2.phi;
    EXPECT_DOUBLE_EQ((grb::type::Float) data.result.spherical, distSpherical(P1, P2));
    EXPECT_DOUBLE_EQ((grb::type::Float) data.result.haversine, distHaversine(P1, P2));
    EXPECT_DOUBLE_EQ((grb::type::Float) data.result.vincenty,  distVincenty(P1, P2));
  }
}

} // namespace testing
