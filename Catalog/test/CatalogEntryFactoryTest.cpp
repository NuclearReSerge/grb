#include "Catalog/CatalogEntryFactory.h"

#include "test/Mock/FactoryTestFixtures.h"

namespace testing
{

class CatalogEntryFactoryTest :
    public FactoryTestFixturesBase<grb::type::CatalogType, grb::CatalogEntry, grb::factory::CatalogEntryFactory>
{
protected:
  void SetUp()
  {
    _invalidType = grb::type::UNDEFINED_CATALOG;
    _invalidName = "undefined-command";
  }
};

} // namespace testing

FACTORY_TEST_FIXTURES(CatalogEntryFactoryTest)

namespace testing
{

TEST_F(CatalogEntryFactoryTest, createName_CatalogEntryGrbcat)
{
  _validType = grb::type::GRBCAT;
  _validName = "grbcat";
  callCreateName();
}

TEST_F(CatalogEntryFactoryTest, createType_CatalogEntryGrbcat)
{
  _validType = grb::type::GRBCAT;
  callCreateType();
}

} // namespace testing
