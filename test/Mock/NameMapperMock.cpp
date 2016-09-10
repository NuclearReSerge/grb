#include "test/Mock/NameMapperMock.h"

namespace
{
  const std::vector<std::string> NAME_LIST
  {
    "NAME_LIST_FIRST",
    "NAME_LIST_LAST"
  };

  const std::string DESCRIPTION = "DESCRIPTION";
}

namespace grb
{
namespace mapper
{

const std::string&
NameMapperMock::getDescription() const
{
  return DESCRIPTION;
}

const std::vector<std::string>&
NameMapperMock::getList() const
{
  return NAME_LIST;
}

} // namespace mapper
} // namespace grb
