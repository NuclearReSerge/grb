#include "Data/DataBaseFormatMapper.h"

namespace
{

static std::vector<std::string> DATABASE_FORMAT_NAMES
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

  // LAST
  "undefined-database-format"
};

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>& DataBaseFormatMapper::getList() const
{
  return DATABASE_FORMAT_NAMES;
}

} // namespace mapper
} // namespace grb
