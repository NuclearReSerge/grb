#include "Data/Region.h"

#include "Tools/test/NameMapperTest.h"
#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

class RegionTest : public NameMapperTest
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
