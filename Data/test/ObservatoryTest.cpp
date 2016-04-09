#include "Data/Observatory.h"

#include "test/NameMapperCommon.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

class ObservatoryTest : public NameMapperCommon
{
  void SetUp()
  {
    _mapper = Observatory::instance();
    _columnType = type::OBSERVATORY;
    _first = "APEX";
    _last = "WXM-HETE2";
    _firstIdx = 0;
    _lastIdx = 35;
  }
};

NAME_MAPPER_TESTS(ObservatoryTest)

}
}
