#include "Data/Catalog.h"

#include "test/Mock/CatalogEntryMock.h"

#include <gmock/gmock.h>

namespace testing
{

class CatalogTest : public Test
{
protected:
  grb::Catalog _catalog;
};

TEST_F(CatalogTest, init)
{
  ASSERT_EQ(grb::type::UNDEFINED_CATALOG, _catalog.getType());
  ASSERT_TRUE(_catalog.empty());
  ASSERT_EQ(0, _catalog.getEntries().size());
  ASSERT_EQ(nullptr, _catalog.createEntry());
}

TEST_F(CatalogTest, addEntry)
{
  grb::CatalogEntryMock* entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  _catalog.getEntries().push_back(entry);
  ASSERT_FALSE(_catalog.empty());
}

TEST_F(CatalogTest, addEntry_clear)
{
  grb::CatalogEntryMock* entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  _catalog.getEntries().push_back(entry);
  ASSERT_FALSE(_catalog.empty());
  _catalog.clear();
  ASSERT_TRUE(_catalog.empty());
}

TEST_F(CatalogTest, constAccess)
{
  const grb::Catalog* catalog = &_catalog;

  ASSERT_EQ(grb::type::UNDEFINED_CATALOG, catalog->getType());
  ASSERT_TRUE(catalog->empty());
  ASSERT_EQ(0, catalog->getEntries().size());
}

} // namespace testing
