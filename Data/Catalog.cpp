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
  try
  {
    return *_catalog[index];
  }
  catch (std::out_of_range& sysExc)
  {
    std::stringstream ss;
    ss << "Catalog of type=" << _type << " [" << GlobalName::getCatalog(_type)
       << "] does not have an entry index=" << index << ", sysExc.what()\n" << sysExc.what();
    Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
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
