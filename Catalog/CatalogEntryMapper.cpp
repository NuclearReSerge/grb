#include "Catalog/CatalogEntryMapper.h"

namespace
{

const std::vector<std::string> CATALOG_ENTRY_NAMES
{
  "grbcat",
  // LAST
  "undefined-catalog"
};

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>& CatalogEntryMapper::getList() const
{
  return CATALOG_ENTRY_NAMES;
}

} // namespace mapper
} // namespace grb
