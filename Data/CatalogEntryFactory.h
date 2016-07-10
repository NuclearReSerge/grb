#include "Common/Singleton.h"
#include "Data/CatalogEntry.h"

#pragma once

namespace grb
{

namespace factory
{

class CatalogEntryFactory
{
public:
  virtual CatalogEntry* create(type::CatalogEntryType type);
  virtual CatalogEntry* create(const std::string& name);
};

}

typedef Singleton<factory::CatalogEntryFactory> CatalogEntryFactory;

}
