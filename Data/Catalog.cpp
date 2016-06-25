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
  for (std::size_t column = 0; column < type::COLUMN_TYPE_UNDEFINED; ++column)
  {
    _unitMap.insert({(type::ColumnType) column, type::NO_UNIT});
  }
}

Catalog::~Catalog()
{
  for(CatalogEntry* entry : _catalog)
  {
    delete entry;
  }
  _catalog.clear();
  _unitMap.clear();
}

type::CatalogType
Catalog::getType() const
{
  return _type;
}

type::UnitType
Catalog::getUnitType(type::ColumnType column) const
{
  return _unitMap.at(column);
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

std::vector<CatalogEntry*>::iterator
Catalog::begin()
{
  return _catalog.begin();
}

std::vector<CatalogEntry*>::iterator
Catalog::end()
{
  return _catalog.end();
}

CatalogEntry&
Catalog::operator[](std::size_t index)
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
  return CatalogEntryFactory::instance()->create(*this);
}

void
Catalog::addEntry(CatalogEntry* entry)
{
  if (entry)
    _catalog.push_back(entry);
}

void
Catalog::setUnitType(type::ColumnType column, type::UnitType unitType)
{
  _unitMap[column] = unitType;
}

}
