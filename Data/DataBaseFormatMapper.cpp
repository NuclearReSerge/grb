#include "Data/DataBaseFormatMapper.h"

namespace grb
{

namespace
{

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
  "test-database-table",
  // LAST
  "undefined-database-table"
};

}

namespace mapper
{

DataBaseFormatMapper::DataBaseFormatMapper()
{
  initiate();
}

const std::vector<std::string>& DataBaseFormatMapper::getList() const
{
  return DATABASE_TABLE_NAMES;
}

}

}
