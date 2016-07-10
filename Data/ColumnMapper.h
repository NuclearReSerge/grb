#include "Common/Singleton.h"
#include "Tools/Mapper.h"

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

  // TEST
  TEST_COLUMN_FLAG,
  TEST_COLUMN_INTEGER,
  TEST_COLUMN_INDEX,
  TEST_COLUMN_INTEGER_RANGE,
  TEST_COLUMN_INDEX_LIST,
  TEST_COLUMN_FLOAT,
  TEST_COLUMN_STRING,
  TEST_COLUMN_STRING_LIST,

  // LAST
  UNDEFINED_COLUMN
};

}

namespace mapper
{

class ColumnMapper : public Mapper<type::ColumnType>
{
public:
  ColumnMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::ColumnMapper> ColumnMapper;

}

