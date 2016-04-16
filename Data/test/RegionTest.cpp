#include "Data/Region.h"

#include "test/Mock/NameMapperCommon.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

class RegionTest : public NameMapperCommon
{
  void SetUp()
  {
    _mapper = Region::instance();
    _columnType = type::REGION;
    _first = "annulus";
    _last = "irregular";
    _firstIdx = 0;
    _lastIdx = 6;
  }
};

NAME_MAPPER_TESTS(RegionTest)

}
}
