#include "Data/CatalogEntry.h"

#include <vector>

#pragma once

namespace grb
{

class Catalog
{
public:
  Catalog()
  {
  }
  ~Catalog()
  {
    _catalog.clear();
  }

  std::vector<CatalogEntry>& get()
  {
    return _catalog;
  }

protected:

private:
  std::vector<CatalogEntry> _catalog;
};

}
