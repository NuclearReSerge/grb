#include <bitset>
#include <chrono>
#include <string>
#include <vector>

#pragma once

namespace grb
{

namespace type
{
// http://heasarc.gsfc.nasa.gov/FTP/heasarc/dbase/dump/
enum DatabaseTableType
{
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
  DATABASE_TABLE_TYPE_UNDEFINED
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
  DUMMY,

  // other
  COORD_LONG,
  COORD_LAT,
  COORD_H,
  COORD_V,

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
  TIMEPOINT,
  COORDINATE,
  STRING,
  STRING_LIST,

  VALUE_TYPE_UNDEFINED
};

enum UnitType
{
  NO_UNIT,
  DEGREE,
  SECOND,
  KILO_EV,
  UNIT_TYPE_UNDEFINED
};

enum CoordinateSystemType
{
  J2000,
  B1950,
  GALACTIC,
  COORDINATE_SYSTEM_UNDEFINED
};

typedef bool Flag;
typedef std::size_t Integer;
typedef int Index;
typedef std::size_t IntegerRange[2];
typedef std::vector<type::Index> IndexList;
typedef double Float;
typedef std::chrono::system_clock::time_point TimePoint;
typedef double Coordinate;
typedef std::string String;
typedef std::vector<std::string> StringList;

typedef std::bitset<COLUMN_TYPE_UNDEFINED> ColumnFlags;

} // namespace type

class GlobalName
{
public:
  GlobalName() = delete;
  GlobalName(const GlobalName& ) = delete;
  GlobalName& operator= (const GlobalName&) = delete;

  static std::string& getDatabaseTable(type::DatabaseTableType dbType);
  static std::string& getColumn(type::ColumnType columnType);
  static std::string& getColumnDescription(type::ColumnType columnType);
  static std::string& getValue(type::ValueType valueType);
  static std::string& getUnit(type::UnitType unitType);
  static std::string& getCoordinateSystem(type::CoordinateSystemType coordinateSystemType);

private:
  static std::string& getWithRangeCheck(std::vector<std::string>& nameList, std::size_t index);

  struct Column
  {
    std::string name;
    std::string description;
  };

  static std::vector<std::string> _dbTableNames;
  static std::vector<Column> _columns;
  static std::vector<std::string> _valueNames;
  static std::vector<std::string> _unitNames;
  static std::vector<std::string> _coordinateSystemNames;
};

}
