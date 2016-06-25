#include "Data/Catalog.h"

#pragma once

namespace grb
{
namespace test
{

class CatalogMock : public Catalog
{
public:
  CatalogMock(type::CatalogType type);

  std::vector<CatalogEntry*>::iterator begin();
  std::vector<CatalogEntry*>::iterator end();
  CatalogEntry& operator[](std::size_t index);

protected:
  CatalogEntry* createEntry();
};

}
}
