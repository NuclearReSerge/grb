#include "test/Mock/CatalogEntryFactoryMock.h"

namespace grb
{
namespace factory
{

CatalogEntryMock*
CatalogEntryFactoryMock::createType(const type::CatalogEntryTypeMock& type)
{
  switch (type)
  {
    case type::CATALOG_ENTRY_MOCK:
      return new CatalogEntryMock;
    default:
      break;
  }

  return nullptr;
}

} // namespace factory
} // namespace grb
