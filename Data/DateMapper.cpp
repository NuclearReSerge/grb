#include "Data/DateMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> DATE_NAMES
{
  "Unix-Date",
  "Julian-Date",
  "Modified-Julian-Date",

  // LAST
  "undefined-date"
};

}

namespace mapper
{

DateMapper::DateMapper()
{
  initiate();
}

const std::vector<std::string>& DateMapper::getList() const
{
  return DATE_NAMES;
}

}

}
