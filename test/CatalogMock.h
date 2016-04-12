#include "Data/Catalog.h"

#pragma once

namespace grb
{
namespace test
{

class CatalogMock : public Catalog
{
public:
  CatalogMock();

protected:
  CatalogEntry* createEntry();
};

}
}
