#include "Data/DateMapper.h"

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

} // namespace


namespace grb
{
namespace mapper
{

const std::vector<std::string>& DateMapper::getList() const
{
  return DATE_NAMES;
}

} // namespace mapper
} // namespace grb
