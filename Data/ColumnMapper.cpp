#include "Data/ColumnMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> COLUMN_NAMES
{
  // HEASARC_GRBCAT
  "record_number",		// Sequential Identification Number for Each Entry in Catalog
  "id",				// Sequential Identification Number for Each Source in Catalog
  "name",			// Burst Designation as GRB YYMMDD
  "alt_names",			// Other Designations for Burst
  "time",			// Time of Burst (UT)
  "time_def",			// Definition of Burst Time
  "observatory",		// Detecting Observatory
  "ra",				// Right Ascension
  "dec",			// Declination
  "coord_flag",			// Quality Flag for RA and Dec
  "region",			// Region
  "afterglow_flag",		// Afterglow Flag
  "reference",			// Reference
  "t50_mod",			// Modifier for t50 (<, >, ~, etc.)
  "t50",			// T_50 (s)
  "t50_error",			// T_50 Error (s)
  "t50_range",			// Energy Range for t50 (keV)
  "t50_emin",			// Minimum of Energy Range for t50 (keV)
  "t50_emax",			// Maximum of Energy Range for t50 (keV)
  "t90_mod",			// Modifier for t90 (<, >, ~, etc.)
  "t90",			// // T_90 (s)
  "t90_error",			// // T_90 Error (s)
  "t90_range",			// Energy Range for t90 (keV)
  "t90_emin",			// Minimum of Energy Range for t90 (keV)
  "t90_emax",			// Maximum of Energy Range for t90 (keV)
  "t_other",			// A Different Duration Measure or duration not specified (s)
  "flux_flag",			// Flux Flag
  "notes",			// Notes
  "flux_notes",			// Flux Notes
  "local_notes",		// Localization Notes
  "class",			// Browse Object Classification

  "Lii",			//
  "Bii",			//
  "horizontal_coordinate",	//
  "vertical_coordinate",	//

  // TEST
  "test_column_flag",		// Test column for flag
  "test_column_integer",	// Test column for integer
  "test_column_index",		// Test column for index
  "test_column_integer_range",	// Test column for integer range
  "test_column_index_list",	// Test column for index list
  "test_column_float",		// Test column for float
  "test_column_string",		// Test column for string
  "test_column_string_list",	// Test column for string list

  // LAST
  "undefined-column",		// Unknown column type
};

}

namespace mapper
{

ColumnMapper::ColumnMapper()
{
  initiate();
}

const std::vector<std::string>& ColumnMapper::getList() const
{
  return COLUMN_NAMES;
}

}

}
