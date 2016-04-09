#include "Common/Global.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class CatalogEntry;

class CatalogEntryFactoryType
{
public:
  CatalogEntry* create(type::CatalogType catType);

protected:
  friend class Singleton<CatalogEntryFactoryType>;
  CatalogEntryFactoryType();
};

typedef Singleton<CatalogEntryFactoryType> CatalogEntryFactory;

}
