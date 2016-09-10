#include "Filter/FilterMapper.h"

namespace
{

const std::vector<std::string> FILTER_NAMES
{
  "filter-none",

  // LAST
  "undefined-filter"
};

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>& FilterMapper::getList() const
{
  return FILTER_NAMES;
}

} // namespace mapper
} // namespace grb
