#include "Data/ObservatoryMapper.h"

#include "test/Mock/NameMapperTestBase.h"

#include <gtest/gtest.h>

namespace testing
{

class ObservatoryMapperTest : public NameMapperTestBase
{
  void SetUp()
  {
    _mapper = grb::ObservatoryMapper::instance();
    _columnType = grb::type::OBSERVATORY;
    _first = "APEX";
    _last = "WXM-HETE2";
    _firstIdx = 0;
    _lastIdx = 35;
  }
};

} // namespace testing

NAME_MAPPER_TESTS(ObservatoryMapperTest)
