#include <bitset>
#include <string>
#include <vector>

#pragma once

namespace grb
{

namespace type
{
// High Energy Astrophysics Science Archive Research Center
// http://heasarc.gsfc.nasa.gov/
enum DatabaseTableType
{
  // HEASARC
  HEASARC_GRBCAT,
  HEASARC_GRBCATAG,
  HEASARC_GRBCATANN,
  HEASARC_GRBCATBOX,
  HEASARC_GRBCATCIRC,
  HEASARC_GRBCATDUAL,
  HEASARC_GRBCATFLUX,
  HEASARC_GRBCATINT,
  HEASARC_GRBCATINTA,
  HEASARC_GRBCATIRR,

  // TEST
  DATABASE_TABLE_TEST,
  // LAST
  DATABASE_TABLE_TYPE_UNDEFINED
};

enum CatalogType
{
  GRBCAT,

  // TEST
  CATALOG_TEST,
  // LAST
  CATALOG_TYPE_UNDEFINED
};

enum ColumnType
{
  // HEASARC_GRBCAT
  RECORD_NUMBER,
  ID,
  NAME,
  ALT_NAMES,
  TIME,
  TIME_DEF,
  OBSERVATORY,
  COORD_RA,
  COORD_DEC,
  COORD_FLAG,
  REGION,
  AFTERGLOW_FLAG,
  REFERENCE,
  T50_MOD,
  T50,
  T50_ERROR,
  T50_RANGE,
  T50_EMIN,
  T50_EMAX,
  T90_MOD,
  T90,
  T90_ERROR,
  T90_RANGE,
  T90_EMIN,
  T90_EMAX,
  T_OTHER,
  FLUX_FLAG,
  NOTES,
  FLUX_NOTES,
  LOCAL_NOTES,
  CLASS,

  // other
  COORD_LONG,
  COORD_LAT,
  COORD_H,
  COORD_V,

  // TEST
  COLUMN_TEST_FLAG,
  COLUMN_TEST_INTEGER,
  COLUMN_TEST_INDEX,
  COLUMN_TEST_INTEGER_RANGE,
  COLUMN_TEST_INDEX_LIST,
  COLUMN_TEST_FLOAT,
  COLUMN_TEST_STRING,
  COLUMN_TEST_STRING_LIST,
  // LAST
  COLUMN_TYPE_UNDEFINED
};

enum ValueType
{
  FLAG,
  INTEGER,
  INDEX,
  INTEGER_RANGE,
  INDEX_LIST,
  FLOAT,
  STRING,
  STRING_LIST,

  // LAST
  VALUE_TYPE_UNDEFINED
};

enum UnitType
{
  NO_UNIT,
  DEGREE,
  SECOND,
  UNIT_UNIX,
  UNIT_JD,
  UNIT_MJD,
  KILO_EV,

  // LAST
  UNIT_TYPE_UNDEFINED
};

enum CoordinateSystemType
{
  J2000,
  B1950,
  GALACTIC,

  // LAST
  COORDINATE_SYSTEM_UNDEFINED
};

enum DateTimeType
{
  UNIX,
  JULIAN_DATE,
  MODIFIED_JULIAN_DATE,

  // LAST
  DATE_TIME_TYPE_UNDEFINED
};

typedef bool                 Flag;
typedef std::size_t          Integer;
typedef int                  Index;
typedef std::vector<Integer> IntegerRange;
typedef std::vector<Index>   IndexList;
typedef double               Float;
typedef std::string          String;
typedef std::vector<String>  StringList;

typedef std::bitset<type::COLUMN_TYPE_UNDEFINED> ColumnFlags;
}

}
