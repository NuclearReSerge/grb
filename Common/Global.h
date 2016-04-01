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

  // other
  COORD_H,
  COORD_LONG,
  COORD_V,
  COORD_LAT,

  COLUMN_TYPE_UNDEFINED
};

enum ValueType
{
  STRING,
  DATE,
  POSITION,
  INTEGER,
  FLAG,
  FLOAT,
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

typedef int Index;
typedef std::chrono::system_clock::time_point Date;
typedef std::bitset<COLUMN_TYPE_UNDEFINED> ColumnFlags;

} // namespace type


class GlobalName
{
public:
  GlobalName() = delete;

  static std::string& getDatabaseTable(type::DatabaseTableType dbType);
  static std::string& getColumn(type::ColumnType columnType);
  static std::string& getValue(type::ValueType valueType);
  static std::string& getUnit(type::UnitType unitType);
  static std::string& getCoordinateSystem(type::CoordinateSystemType coordinateSystemType);

private:
  static std::string& getWithRangeCheck(std::vector<std::string>& nameList, std::size_t index);

  static std::vector<std::string> _dbTableNames;
  static std::vector<std::string> _columnNames;
  static std::vector<std::string> _valueNames;
  static std::vector<std::string> _unitNames;
  static std::vector<std::string> _coordinateSystemNames;
};

}
