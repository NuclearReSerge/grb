#include "Common/Factory.h"
#include "Data/CatalogEntry.h"
#include "Data/CatalogEntryMapper.h"

#pragma once

FACTORY_CLASS_H(CatalogEntryFactory, type::CatalogEntryType, CatalogEntry, CatalogEntryMapper)
