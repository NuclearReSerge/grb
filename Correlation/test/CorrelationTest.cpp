#include "test/Mock/CatalogMock.h"
#include "test/Mock/CorrelationMock.h"

#include <gtest/gtest.h>

namespace testing
{

class CorrelationTest : public Test
{
protected:
  void SetUp()
  {
  }

  void TearDown()
  {
  }

  grb::type::Float _range;
  std::size_t _points;
  grb::type::Float _delta;

  grb::CorrelationMock _correlation { grb::type::UNDEFINED_CORRELATION };
};

TEST_F(CorrelationTest, initial)
{

  ASSERT_EQ(grb::type::UNDEFINED_CORRELATION, _correlation.getType());

  ASSERT_FLOAT_EQ((grb::type::Float) 1.0, _correlation.getxRange());
  ASSERT_EQ((std::size_t) 0, _correlation.getxPoints());
  ASSERT_FLOAT_EQ((grb::type::Float) 0.0, _correlation.getxDelta());

  ASSERT_FLOAT_EQ((grb::type::Float) 1.0, _correlation.getyRange());
  ASSERT_EQ((std::size_t) 0, _correlation.getyPoints());
  ASSERT_FLOAT_EQ((grb::type::Float) 0.0, _correlation.getyDelta());
}

TEST_F(CorrelationTest, setAxis_Positive)
{
  _range = M_PI;
  _points = 180;
  _delta = 180.0 / M_PI ;
  _correlation.setXAxis(_range, _points);

  ASSERT_FLOAT_EQ(_range, _correlation.getxRange());
  ASSERT_EQ(_points, _correlation.getxPoints());
  ASSERT_FLOAT_EQ(_delta, _correlation.getxDelta());

  _range = M_E;
  _points = 256;
  _delta = 256.0 / M_E;
  _correlation.setYAxis(_range, _points);

  ASSERT_FLOAT_EQ(_range, _correlation.getyRange());
  ASSERT_EQ(_points, _correlation.getyPoints());
  ASSERT_FLOAT_EQ(_delta, _correlation.getyDelta());
}

TEST_F(CorrelationTest, setAxis_Negative)
{
  _range = 0.0;
  _points = 180;
  _correlation.setXAxis(_range, _points);

  ASSERT_FLOAT_EQ((grb::type::Float) 1.0, _correlation.getxRange());
  ASSERT_EQ((std::size_t) 0, _correlation.getxPoints());
  ASSERT_FLOAT_EQ((grb::type::Float) 0.0, _correlation.getxDelta());

  _range = -0.0;
  _points = 256;
  _correlation.setYAxis(_range, _points);

  ASSERT_FLOAT_EQ((grb::type::Float) 1.0, _correlation.getyRange());
  ASSERT_EQ((std::size_t) 0, _correlation.getyPoints());
  ASSERT_FLOAT_EQ((grb::type::Float) 0.0, _correlation.getyDelta());
}

} // namespace testing
