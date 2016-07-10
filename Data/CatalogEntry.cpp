#include "Data/CatalogEntry.h"

namespace grb
{

CatalogEntry::CatalogEntry(type::CatalogEntryType type)
  : _type(type)
{
}

CatalogEntry::~CatalogEntry()
{
}

type::CatalogEntryType
CatalogEntry::getType() const
{
  return _type;
}

}
