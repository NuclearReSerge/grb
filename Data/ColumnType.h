#pragma once

namespace grb
{
namespace type
{

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

  // LAST
  UNDEFINED_COLUMN
};

} // namespace type
} // namespace grb
