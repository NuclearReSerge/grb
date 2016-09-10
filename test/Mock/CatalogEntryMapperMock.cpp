#include "test/Mock/CatalogEntryMapperMock.h"

namespace
{

const std::vector<std::string> CATALOG_ENTRY_MOCK_NAMES
{
  "catalog-entry-mock",
  // LAST
  "undefined-catalog-entry-mock"
};

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>&
CatalogEntryMapperMock::getList() const
{
  return CATALOG_ENTRY_MOCK_NAMES;
}

} // namespace mapper
} // namespace grb
