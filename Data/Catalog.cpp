#include "Data/Catalog.h"

#include "Common/Exception.h"
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
Catalog::empty() const
{
  return _catalog.empty();
}

std::size_t
Catalog::size() const
{
  return _catalog.size();
}

std::vector<CatalogEntry*>::const_iterator
Catalog::begin() const
{
    return _catalog.begin();
}

std::vector<CatalogEntry*>::const_iterator
Catalog::end() const
{
    return _catalog.end();
}

const CatalogEntry&
Catalog::operator[](std::size_t index) const
{
  if (index < _catalog.size())
    return *_catalog[index];

  std::stringstream ss;
  ss << "Catalog type=" << _type << " [" << GlobalName::getCatalog(_type)
     << "]. Index=" << index << " is out of range.";
  Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
  throw exc;
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

}
