#include "Filter/FilterCmdMapper.h"

namespace
{

const std::vector<std::string> FILTER_CMD_NAMES
{
  "create",
  "help",

  // LAST
  "undefined-filter-cmd"
};

} // namespace


namespace grb
{
namespace mapper
{

const std::vector<std::string>& FilterCmdMapper::getList() const
{
  return FILTER_CMD_NAMES;
}

} // namespace mapper
} // namespace grb
