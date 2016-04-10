#include "Data/Catalog.h"

#include "Common/GlobalName.h"
#include "Data/CatalogEntry.h"
#include "Data/CatalogEntryFactory.h"

#include <sstream>

namespace grb
{

Catalog::Catalog(type::CatalogType type)
  : _type(type)
{
}

Catalog::~Catalog()
{
  for(CatalogEntry* entry : _catalog)
  {
    delete entry;
  }
  _catalog.clear();
}

type::CatalogType
Catalog::getType() const
{
  return _type;
}

bool
Catalog::isEmpty() const
{
  return _catalog.empty();
}

std::size_t
Catalog::getSize() const
{
  return _catalog.size();
}

CatalogEntry*
Catalog::createEntry()
{
  return CatalogEntryFactory::instance()->create(_type);
}

void
Catalog::addEntry(CatalogEntry* entry)
{
  if (entry)
    _catalog.push_back(entry);
}

const CatalogEntry&
Catalog::getEntry(std::size_t index) const throw(Exception)
{
  if (index < _catalog.size())
    return *_catalog[index];

  std::stringstream ss;
  ss << "Catalog of type=" << _type << "[" << GlobalName::getCatalog(_type)
     << "] does not have an entry of index=" << index;
  Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
  throw exc;
}

}
