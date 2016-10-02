#include "Data/CatalogEntryMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class CatalogEntryMapperTest
    : public MapperTestFixturesBase<grb::type::CatalogEntryType, grb::mapper::CatalogEntryMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_CATALOG_ENTRY;
    _invalidType = (grb::type::CatalogEntryType) -1;

    _validName = "undefined-catalog-entry";
    _invalidName = "catalog-entry-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(CatalogEntryMapperTest)
