#pragma once

#include "Common/Factory.h"
#include "Catalog/CatalogEntry.h"
#include "Catalog/CatalogEntryMapper.h"

FACTORY_CLASS_H(CatalogEntryFactory, type::CatalogType, CatalogEntry, CatalogEntryMapper)
