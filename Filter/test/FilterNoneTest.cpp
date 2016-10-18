#include "Filter/FilterNone.h"

#include <gmock/gmock.h>

namespace testing
{

class FilterNoneTest : public Test
{
protected:
  grb::FilterNone _filter;
};

TEST_F(FilterNoneTest, init)
{
  ASSERT_EQ(grb::type::FILTER_NONE, _filter.getType());
}

} // namespace testing
