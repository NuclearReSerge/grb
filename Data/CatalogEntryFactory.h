#include "Common/Global.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class Catalog;
class CatalogEntry;

class CatalogEntryFactoryType
{
public:
  CatalogEntry* create(const Catalog& catalog);

protected:
  friend class Singleton<CatalogEntryFactoryType>;
  CatalogEntryFactoryType();
};

typedef Singleton<CatalogEntryFactoryType> CatalogEntryFactory;

}
