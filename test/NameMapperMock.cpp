#include "test/NameMapperMock.h"

namespace grb
{
namespace test
{

namespace
{
  const NameMapper::VectorString NAME_LIST
  {
    "NAME_LIST_FIRST",
    "NAME_LIST_LAST"
  };

  const std::string DESCRIPTION = "DESCRIPTION";
}


NameMapperMock::NameMapperMock()
  : NameMapper(type::COLUMN_TEST_INDEX, DESCRIPTION)
{
  initiate();
}

const NameMapper::VectorString&
NameMapperMock::getNameList() const
{
  return NAME_LIST;
}

}
}
