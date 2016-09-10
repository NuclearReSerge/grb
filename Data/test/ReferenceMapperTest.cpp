#include "Data/ReferenceMapper.h"

#include "test/Mock/NameMapperTestBase.h"

#include <gtest/gtest.h>

namespace testing
{

class ReferenceMapperTest : public NameMapperTestBase
{
  void SetUp()
  {
    _mapper = grb::ReferenceMapper::instance();
    _columnType = grb::type::REFERENCE;
    _first = "1974ApJ...188L...1S";
    _last = "Mitrofanov et al. (1990)";
    _firstIdx = 0;
    _lastIdx = 329;
  }
};

} // namespace testing

NAME_MAPPER_TESTS(ReferenceMapperTest)
