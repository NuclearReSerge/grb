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
  if (columnType >= _columns.size())
    return _columns[_columns.size()-1].name;

  return _columns[columnType].name;
}

std::string&
GlobalName::getColumnDescription(type::ColumnType columnType)
{
  if (columnType >= _columns.size())
    return _columns[_columns.size()-1].description;

  return _columns[columnType].description;
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

  "unknown database table type"
};

std::vector<GlobalName::Column> GlobalName::_columns
{
  { "record_number", "Sequential Identification Number for Each Entry in Catalog" },
  { "id", "Sequential Identification Number for Each Source in Catalog" },
  { "name", "Burst Designation as GRB YYMMDD" },
  { "alt_names", "Other Designations for Burst" },
  { "time", "Time of Burst (UT)" },
  { "time_def", "Definition of Burst Time" },
  { "observatory", "Detecting Observatory" },
  { "ra", "Right Ascension" },
  { "dec", "Declination" },
  { "coord_flag", "Quality Flag for RA and Dec" },
  { "region", "Region" },
  { "afterglow_flag", "Afterglow Flag" },
  { "reference", " Reference" },
  { "t50_mod", "Modifier for t50 (<, >, ~, etc.)" },
  { "t50", "T_50 (s)" },
  { "t50_error", "T_50 Error (s)" },
  { "t50_range", "Energy Range for t50 (keV)" },
  { "t50_emin", "Minimum of Energy Range for t50 (keV)" },
  { "t50_emax", "Maximum of Energy Range for t50 (keV)" },
  { "t90_mod", "Modifier for t90 (<, >, ~, etc.)" },
  { "t90", "// T_90 (s)" },
  { "t90_error", "// T_90 Error (s)" },
  { "t90_range", "Energy Range for t90 (keV)" },
  { "t90_emin", "Minimum of Energy Range for t90 (keV)" },
  { "t90_emax", "Maximum of Energy Range for t90 (keV)" },
  { "t_other", "A Different Duration Measure or duration not specified (s)" },
  { "flux_flag", "Flux Flag" },
  { "notes", "Notes" },
  { "flux_notes", "Flux Notes" },
  { "local_notes", "Localization Notes" },
  { "class", "Browse Object Classification" },
  { "DUMMY", "dummy column; usually after the last delimiter" },

  { "Lii", "" },
  { "Bii", "" },
  { "horizontal coordinate", "" },
  { "vertical coordinate", "" },

  { "unknown column type", "" }
};

std::vector<std::string> GlobalName::_valueNames
{
  "flag",
  "integer",
  "index",
  "integer range",
  "index list",
  "float",
  "time point",
  "coordinate",
  "string",
  "string list",

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
