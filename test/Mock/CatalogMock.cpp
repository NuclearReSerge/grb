#include "Common/Exception.h"
#include "Common/GlobalName.h"

#include <sstream>

#include "test/Mock/CatalogMock.h"
#include "test/Mock/CatalogEntryMock.h"

namespace grb
{
namespace test
{

CatalogMock::CatalogMock(type::CatalogType type)
  : Catalog(type)
{
}

std::vector<CatalogEntry*>::iterator
CatalogMock::begin()
{
  return _catalog.begin();
}

std::vector<CatalogEntry*>::iterator
CatalogMock::end()
{
  return _catalog.end();
}

CatalogEntry&
CatalogMock::operator[](std::size_t index)
{
  if (index < _catalog.size())
    return *_catalog[index];

  std::stringstream ss;
  ss << "Catalog type=" << getType() << " [" << GlobalName::getCatalog(getType())
     << "]. Index=" << index << " is out of range.";
  Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
  throw exc;
}

CatalogEntry*
CatalogMock::createEntry()
{
  return new CatalogEntryMock(*this);
}

}
}
