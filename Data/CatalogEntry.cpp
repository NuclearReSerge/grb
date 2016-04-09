#include "Data/CatalogEntry.h"

namespace grb
{

CatalogEntry::CatalogEntry(type::CatalogType type)
  : _type(type)
{
}

CatalogEntry::~CatalogEntry()
{
}

type::CatalogType
CatalogEntry::getType() const
{
  return _type;
}

}
