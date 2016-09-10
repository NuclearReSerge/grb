#include "Data/RegionMapper.h"

#include "test/Mock/NameMapperTestBase.h"

#include <gtest/gtest.h>

namespace testing
{

class RegionMapperTest : public NameMapperTestBase
{
  void SetUp()
  {
    _mapper = grb::RegionMapper::instance();
    _columnType = grb::type::REGION;
    _first = "annulus";
    _last = "irregular";
    _firstIdx = 0;
    _lastIdx = 6;
  }
};

} // namespace testing

NAME_MAPPER_TESTS(RegionMapperTest)
