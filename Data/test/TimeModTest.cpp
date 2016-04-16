#include "Data/TimeMod.h"

#include "test/Mock/NameMapperCommon.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

class Time50ModTest : public NameMapperCommon
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

NAME_MAPPER_TESTS(Time50ModTest)

class Time90ModTest : public NameMapperCommon
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

NAME_MAPPER_TESTS(Time90ModTest)

}
}
