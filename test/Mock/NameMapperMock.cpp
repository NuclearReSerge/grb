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
  : NameMapper(type::TEST_COLUMN_INDEX, DESCRIPTION)
{
  initiate();
}

const std::vector<std::string>& NameMapperMock::getList() const
{
  return NAME_LIST;
}

}
}
