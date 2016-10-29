#include "Correlation/CorrelationTimeArcGrbcat.h"

#include <gmock/gmock.h>

namespace testing
{

class CorrelationTimeArcGrbcatTest : public Test
{
protected:
  grb::CorrelationTimeArcGrbcat _corr;

};

TEST_F(CorrelationTimeArcGrbcatTest, init)
{
  ASSERT_EQ(grb::type::CORRELATION_GRBCAT_DTDARC, _corr.getType());
}

} // namespace testing
