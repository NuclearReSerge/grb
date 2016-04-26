#include "Analyzer/GreatCircleDistance.h"

#include "test/Mock/CoordinatesMock.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

class GreatCircleDistanceTest : public Test
{
protected:
  void SetUp()
  {
  }
  void TearDown()
  {
  }
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

TEST_F(GreatCircleDistanceTest, XYZPoints_SphericalLawFormula)
{
  GreatCircleDistance distance(type::SPHERICAL_LAW_OF_COSINES);
  CoordinatesMock PX(type::GALACTIC);
  CoordinatesMock PY(type::GALACTIC);
  CoordinatesMock PZZ(type::GALACTIC); // Zenith
  CoordinatesMock PZN(type::GALACTIC); // Nadir

  PX.getHorizontal() = 0.0;
  PX.getVertical() = 0.0;

  PY.getHorizontal() = M_PI_2l ;
  PY.getVertical() = 0.0;

  PZZ.getHorizontal() = 0.0;
  PZZ.getVertical() = M_PI_2l;

  PZN.getHorizontal() = M_PIl; // can be anything
  PZN.getVertical() = -M_PI_2l;


  EXPECT_DOUBLE_EQ((type::Float) M_PI_2l, distance(PX, PY));
  EXPECT_DOUBLE_EQ((type::Float) M_PI_2l, distance(PY, PX));

  EXPECT_DOUBLE_EQ((type::Float) M_PI_2l, distance(PY, PZZ));
  EXPECT_DOUBLE_EQ((type::Float) M_PI_2l, distance(PY, PZN));
  EXPECT_DOUBLE_EQ((type::Float) M_PI_2l, distance(PZZ, PX));
  EXPECT_DOUBLE_EQ((type::Float) M_PI_2l, distance(PZN, PX));
}

}
}
