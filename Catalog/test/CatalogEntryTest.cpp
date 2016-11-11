#include "test/Mock/CatalogEntryMock.h"

#include <gmock/gmock.h>

namespace testing
{

class CatalogEntryTest : public Test
{
protected:
  void SetUp()
  {
    _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  }
  void TearDown()
  {
    delete _entry;
  }

  grb::CatalogEntry* _entry;
};

TEST_F(CatalogEntryTest, init)
{
  ASSERT_EQ(grb::type::UNDEFINED_CATALOG, _entry->getType());
}

} // namespace testing
