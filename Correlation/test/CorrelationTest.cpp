#include "test/Mock/CatalogMock.h"
#include "test/Mock/CorrelationMock.h"

#include <gtest/gtest.h>

namespace testing
{

class CorrelationTest : public Test
{

};

TEST_F(CorrelationTest, initial)
{
  grb::CorrelationMock corr;

  ASSERT_EQ(grb::type::UNDEFINED_CORRELATION, corr.getType());

  ASSERT_FLOAT_EQ((grb::type::Float) 1.0, corr.getxRange());
  ASSERT_EQ((std::size_t) 0, corr.getxPoints());
  ASSERT_FLOAT_EQ((grb::type::Float) 0.0, corr.getxDelta());

  ASSERT_FLOAT_EQ((grb::type::Float) 1.0, corr.getyRange());
  ASSERT_EQ((std::size_t) 0, corr.getyPoints());
  ASSERT_FLOAT_EQ((grb::type::Float) 0.0, corr.getyDelta());
}

TEST_F(CorrelationTest, setAxis_Positive)
{
  grb::CorrelationMock corr;
  grb::type::Float range;
  std::size_t points;
  grb::type::Float delta;

  range = M_PI;
  points = 180;
  delta = 180.0 / M_PI ;
  corr.setXAxis(range, points);

  ASSERT_FLOAT_EQ(range, corr.getxRange());
  ASSERT_EQ(points, corr.getxPoints());
  ASSERT_FLOAT_EQ(delta, corr.getxDelta());

  range = M_E;
  points = 256;
  delta = 256.0 / M_E;
  corr.setYAxis(range, points);

  ASSERT_FLOAT_EQ(range, corr.getyRange());
  ASSERT_EQ(points, corr.getyPoints());
  ASSERT_FLOAT_EQ(delta, corr.getyDelta());
}

TEST_F(CorrelationTest, setAxis_Negative)
{
  grb::CorrelationMock corr;
  grb::type::Float range;
  std::size_t points;

  range = 0.0;
  points = 180;
  corr.setXAxis(range, points);

  ASSERT_FLOAT_EQ((grb::type::Float) 1.0, corr.getxRange());
  ASSERT_EQ((std::size_t) 0, corr.getxPoints());
  ASSERT_FLOAT_EQ((grb::type::Float) 0.0, corr.getxDelta());

  range = -0.0;
  points = 256;
  corr.setYAxis(range, points);

  ASSERT_FLOAT_EQ((grb::type::Float) 1.0, corr.getyRange());
  ASSERT_EQ((std::size_t) 0, corr.getyPoints());
  ASSERT_FLOAT_EQ((grb::type::Float) 0.0, corr.getyDelta());
}

} // namespace testing
