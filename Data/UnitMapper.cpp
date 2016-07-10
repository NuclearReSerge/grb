#include "Data/UnitMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> UNIT_NAMES
{
  "",
  "deg",
  "s",
  "MJD"
  "keV",
  // LAST
  "undefined-unit"
};

}

namespace mapper
{

UnitMapper::UnitMapper()
{
  initiate();
}

const std::vector<std::string>& UnitMapper::getList() const
{
  return UNIT_NAMES;
}

}

}
