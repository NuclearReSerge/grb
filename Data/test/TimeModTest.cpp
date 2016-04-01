#include "Data/TimeMod.h"

#include "Tools/test/NameMapperTest.h"
#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

class Time50ModTest : public NameMapperTest
{
  void SetUp()
  {
    _mapper = Time50Mod::instance();
    _columnType = type::T50_MOD;
    _first = "<";
    _last = "~";
    _firstIdx = 0;
    _lastIdx = 2;
  }
};

class Time90ModTest : public NameMapperTest
{
  void SetUp()
  {
    _mapper = Time90Mod::instance();
    _columnType = type::T90_MOD;
    _first = "<";
    _last = "~";
    _firstIdx = 0;
    _lastIdx = 2;
  }
};


NAME_MAPPER_TESTS(Time50ModTest)

NAME_MAPPER_TESTS(Time90ModTest)

}
}
