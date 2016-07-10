#include "Data/ValueMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> VALUE_NAMES
{
  "flag",
  "integer",
  "index",
  "integer-range",
  "index-list",
  "float",
  "string",
  "string-list",

  // LAST
  "undefined-value"
};

}

namespace mapper
{

ValueMapper::ValueMapper()
{
  initiate();
}

const std::vector<std::string>& ValueMapper::getList() const
{
  return VALUE_NAMES;
}

}

}
