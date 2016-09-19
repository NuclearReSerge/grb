#include "Data/Catalog.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class CatalogMock : public Catalog
{
public:
  CatalogMock()
    : Catalog()
  {
  }

  MOCK_METHOD0(createEntry, CatalogEntry*());

};

} // namespace grb
