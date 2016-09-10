#include "Common/Factory.h"

#include "test/Mock/CatalogEntryMock.h"
#include "test/Mock/CatalogEntryMapperMock.h"

#pragma once

FACTORY_CLASS_H(CatalogEntryFactoryMock, type::CatalogEntryTypeMock, CatalogEntryMock, CatalogEntryMapperMock)
