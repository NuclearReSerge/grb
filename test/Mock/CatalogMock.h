#include "Data/Catalog.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class CatalogMock : public Catalog
{
public:
  CatalogMock(const type::CatalogType& type)
    : Catalog(type)
  {
  }

  MOCK_METHOD0(createEntry, CatalogEntry*());

};

} // namespace grb
