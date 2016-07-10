#include "Data/CatalogEntryFactory.h"

#include "Data/CatalogEntryGrbcat.h"

namespace grb
{

namespace factory
{

CatalogEntry*
CatalogEntryFactory::create(type::CatalogEntryType type)
{
  switch (type)
  {
    case type::GRBCAT_ENTRY:
      return new CatalogEntryGrbcat;
    default:
      break;
  }
  return nullptr;
}

CatalogEntry*
CatalogEntryFactory::create(const std::string& name)
{
  type::CatalogEntryType type;
  try
  {
    type = CatalogEntryMapper::instance()->getValue(name);
  }
  catch (Exception& exc)
  {
    return nullptr;
  }
  return create(type);
}

}

}
