#include "Data/CatalogEntryMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class CatalogEntryMapperTest
    : public MapperTestFixturesBase<grb::type::CatalogType, grb::mapper::CatalogEntryMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_CATALOG;
    _invalidType = (grb::type::CatalogType) -1;

    _validName = "undefined-catalog";
    _invalidName = "catalog-entry-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(CatalogEntryMapperTest)
