#include "Data/TimeModMapper.h"

#include "test/Mock/NameMapperTestBase.h"

#include <gtest/gtest.h>

namespace testing
{

class Time50ModMapperTest : public NameMapperTestBase
{
  void SetUp()
  {
    _mapper = grb::Time50ModMapper::instance();
    _columnType = grb::type::T50_MOD;
    _first = "<";
    _last = "~";
    _firstIdx = 0;
    _lastIdx = 2;
  }
};

class Time90ModMapperTest : public NameMapperTestBase
{
  void SetUp()
  {
    _mapper = grb::Time90ModMapper::instance();
    _columnType = grb::type::T90_MOD;
    _first = "<";
    _last = "~";
    _firstIdx = 0;
    _lastIdx = 2;
  }
};

} // namespace testing

NAME_MAPPER_TESTS(Time50ModMapperTest)
NAME_MAPPER_TESTS(Time90ModMapperTest)
