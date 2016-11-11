#include "Database/DatabaseMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class DatabaseMapperTest
    : public MapperTestFixturesBase<grb::type::DatabaseType, grb::mapper::DatabaseMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_DATABASE;
    _invalidType = (grb::type::DatabaseType) -1;

    _validName = "undefined-database-format";
    _invalidName = "database-format-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(DatabaseMapperTest)
