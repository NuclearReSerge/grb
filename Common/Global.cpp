#include "Global.h"

namespace grb
{

std::string&
GlobalName::getDatabaseTable(type::DatabaseTableType dbType)
{
  return getWithRangeCheck(_dbTableNames, dbType);
}

std::string&
GlobalName::getColumn(type::ColumnType columnType)
{
  return getWithRangeCheck(_columnNames, columnType);
}

std::string&
GlobalName::getValue(type::ValueType valueType)
{
  return getWithRangeCheck(_valueNames, valueType);
}

std::string&
GlobalName::getUnit(type::UnitType unitType)
{
  return getWithRangeCheck(_unitNames, unitType);
}

std::string&
GlobalName::getCoordinateSystem(type::CoordinateSystemType coordinateSystemType)
{
  return getWithRangeCheck(_coordinateSystemNames, coordinateSystemType);
}

std::string&
GlobalName::getWithRangeCheck(std::vector<std::string>& nameList, std::size_t index)
{
  if (index >= nameList.size())
  {
    return nameList[nameList.size()-1];
  }
  return nameList[index];
}

std::vector<std::string> GlobalName::_dbTableNames
{
  "heasarc_grbcat",
  "heasarc_grbcatag",
  "heasarc_grbcatann",
  "heasarc_grbcatbox",
  "heasarc_grbcatcirc",
  "heasarc_grbcatdual",
  "heasarc_grbcatflux",
  "heasarc_grbcatint",
  "heasarc_grbcatinta",
  "heasarc_grbcatirr",
  "unknown databese table type"
};

std::vector<std::string> GlobalName::_columnNames
{
  "record_number",
  "id",
  "name",
  "alt_names",
  "time",
  "time_def",
  "observatory",
  "ra",
  "dec",
  "coord_flag",
  "region",
  "afterglow_flag",
  "reference",
  "t50_mod",
  "t50",
  "t50_error",
  "t50_range",
  "t50_emin",
  "t50_emax",
  "t90_mod",
  "t90",
  "t90_error",
  "t90_range",
  "t90_emin",
  "t90_emax",
  "t_other",
  "flux_flag",
  "notes",
  "flux_notes",
  "local_notes",
  "class",

  "horizontal coordinate",
  "Lii",
  "vertical coordinate",
  "Bii",

  "unknown column type"
};

std::vector<std::string> GlobalName::_valueNames
{
  "string",
  "date",
  "position",
  "integer",
  "flag",
  "value",
  "unknown value type"
};

std::vector<std::string> GlobalName::_unitNames
{
  "",
  "deg",
  "s",
  "keV",
  "unknown unit type"
};

std::vector<std::string> GlobalName::_coordinateSystemNames
{
  "J2000",
  "B1950",
  "galactic",
  "unknown coordinate system"
};

}
