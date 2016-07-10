#include "Data/CatalogEntryMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> CATALOG_ENTRY_NAMES
{
  "grbcat-entry",
  // TEST
  "test-catalog-entry",
  // LAST
  "undefined-catalog-entry"
};

}

namespace mapper
{

CatalogEntryMapper::CatalogEntryMapper()
{
  initiate();
}

const std::vector<std::string>& CatalogEntryMapper::getList() const
{
  return CATALOG_ENTRY_NAMES;
}

type::CatalogEntryType
CatalogEntryMapper::convertDataBaseFormat(type::DatabaseTableType dbType)
{
  switch (dbType)
  {
    case type::HEASARC_GRBCAT:
      return type::GRBCAT_ENTRY;

    case type::HEASARC_GRBCATAG:
    case type::HEASARC_GRBCATANN:
    case type::HEASARC_GRBCATBOX:
    case type::HEASARC_GRBCATCIRC:
    case type::HEASARC_GRBCATDUAL:
    case type::HEASARC_GRBCATFLUX:
    case type::HEASARC_GRBCATINT:
    case type::HEASARC_GRBCATINTA:
    case type::HEASARC_GRBCATIRR:
    default:
      break;
  }
  return type::UNDEFINED_CATALOG_ENTRY;
}

}

}
