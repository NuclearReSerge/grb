#include "Filter/FilterMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> FILTER_NAMES
{
  "filter-none",

  // LAST
  "undefined-filter"
};

}

namespace mapper
{

FilterMapper::FilterMapper()
{
  initiate();
}

const std::vector<std::string>& FilterMapper::getList() const
{
  return FILTER_NAMES;
}

}

}
