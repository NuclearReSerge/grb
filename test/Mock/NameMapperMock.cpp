#include "test/Mock/NameMapperMock.h"

namespace grb
{
namespace test
{

namespace
{
  const std::vector<std::string> NAME_LIST
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

const std::vector<std::string>& NameMapperMock::getNameList() const
{
  return NAME_LIST;
}

}
}
