#include "Data/Reference.h"

#include "Tools/test/NameMapperTest.h"
#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

class ReferenceTest : public NameMapperTest
{
  void SetUp()
  {
    _mapper = Reference::instance();
    _columnType = type::REFERENCE;
    _first = "1974ApJ...188L...1S";
    _last = "Mitrofanov et al. (1990)";
    _firstIdx = 0;
    _lastIdx = 329;
  }
};

NAME_MAPPER_TESTS(ReferenceTest)

}
}
