#include "Common/Singleton.h"
#include "Tools/Mapper.h"

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
  TEST_DATABASE_TABLE,
  // LAST
  UNDEFINED_DATABASE_TABLE
};

}

namespace mapper
{

class DataBaseFormatMapper : public Mapper<type::DatabaseTableType>
{
public:
  DataBaseFormatMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::DataBaseFormatMapper> DataBaseFormatMapper;

}
