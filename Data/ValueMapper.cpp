#include "Data/ValueMapper.h"

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

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>& ValueMapper::getList() const
{
  return VALUE_NAMES;
}

} // namespace mapper
} // namespace grb
