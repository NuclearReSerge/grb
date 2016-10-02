#include "Data/UnitMapper.h"

namespace
{

const std::vector<std::string> UNIT_NAMES
{
  "",
  "deg",
  "s",
  "Unix",
  "JD",
  "MJD",
  "keV",
  // LAST
  "undefined-unit"
};

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>& UnitMapper::getList() const
{
  return UNIT_NAMES;
}

} // namespace mapper
} // namespace grb
