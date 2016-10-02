#include "Data/CatalogEntryFactory.h"

#include "test/Mock/FactoryTestFixtures.h"

namespace testing
{

class CatalogEntryFactoryTest :
    public FactoryTestFixturesBase<grb::type::CatalogEntryType, grb::CatalogEntry, grb::factory::CatalogEntryFactory>
{
protected:
  void SetUp()
  {
    _invalidType = grb::type::UNDEFINED_CATALOG_ENTRY;
    _invalidName = "undefined-command";
  }
};

} // namespace testing

FACTORY_TEST_FIXTURES(CatalogEntryFactoryTest)

namespace testing
{

TEST_F(CatalogEntryFactoryTest, createName_CatalogEntryGrbcat)
{
  _validType = grb::type::GRBCAT_ENTRY;
  _validName = "grbcat-entry";
  callCreateName();
}

TEST_F(CatalogEntryFactoryTest, createType_CatalogEntryGrbcat)
{
  _validType = grb::type::GRBCAT_ENTRY;
  callCreateType();
}

} // namespace testing
