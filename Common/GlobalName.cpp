#include "Common/GlobalName.h"

namespace grb
{

struct Column
{
  std::string name;
  std::string description;
};

static std::vector<std::string> DATABASE_TABLE_NAMES
{
  // HEASARC
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
  // TEST
  "database table test",
  // LAST
  "unknown database table type"
};

static std::vector<std::string> CATALOG_NAMES
{
  "GRBCAT",
  // TEST
  "catalog test",
  // LAST
  "unknown catalog type"
};

static std::vector<Column> COLUMN_NAMES
{
  // HEASARC_GRBCAT
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

  { "Lii", "" },
  { "Bii", "" },
  { "horizontal coordinate", "" },
  { "vertical coordinate", "" },

  // TEST
  { "column_test_flag", "Test column for flag" },
  { "column_test_integer", "Test column for integer" },
  { "column_test_index", "Test column for index" },
  { "column_test_integer_range", "Test column for integer range" },
  { "column_test_index_list", "Test column for index list" },
  { "column_test_float", "Test column for float" },
  { "column_test_string", "Test column for string" },
  { "column_test_string_list", "Test column for string list" },
  // LAST
  { "unknown_column_type", "Unknown column type" }
};

static std::vector<std::string> VALUE_NAMES
{
  "flag",
  "integer",
  "index",
  "integer range",
  "index list",
  "float",
  "string",
  "string list",
  // LAST
  "unknown value type"
};

static std::vector<std::string> UNIT_NAMES
{
  "",
  "deg",
  "s",
  "MJD"
  "keV",
  // LAST
  "unknown unit type"
};

static std::vector<std::string> COORDINATE_SYSTEM_NAMES
{
  "J2000",
  "B1950",
  "galactic",
  // LAST
  "unknown coordinate system"
};

std::string&
GlobalName::getDatabaseTable(type::DatabaseTableType dbType)
{
  return getWithRangeCheck(DATABASE_TABLE_NAMES, dbType);
}

std::string&
GlobalName::getCatalog(type::CatalogType catType)
{
  return getWithRangeCheck(CATALOG_NAMES, catType);
}

std::string&
GlobalName::getColumn(type::ColumnType columnType)
{
  if (columnType >= COLUMN_NAMES.size())
    return COLUMN_NAMES[COLUMN_NAMES.size()-1].name;

  return COLUMN_NAMES[columnType].name;
}

std::string&
GlobalName::getColumnDescription(type::ColumnType columnType)
{
  if (columnType >= COLUMN_NAMES.size())
    return COLUMN_NAMES[COLUMN_NAMES.size()-1].description;

  return COLUMN_NAMES[columnType].description;
}


std::string&
GlobalName::getValue(type::ValueType valueType)
{
  return getWithRangeCheck(VALUE_NAMES, valueType);
}

std::string&
GlobalName::getUnit(type::UnitType unitType)
{
  return getWithRangeCheck(UNIT_NAMES, unitType);
}

std::string&
GlobalName::getCoordinateSystem(type::CoordinateSystemType coordinateSystemType)
{
  return getWithRangeCheck(COORDINATE_SYSTEM_NAMES, coordinateSystemType);
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

}
