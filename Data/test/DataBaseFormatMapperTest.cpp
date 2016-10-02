#include "Data/DataBaseFormatMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class DataBaseFormatMapperTest
    : public MapperTestFixturesBase<grb::type::DataBaseFormatType, grb::mapper::DataBaseFormatMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_DATABASE_FORMAT;
    _invalidType = (grb::type::DataBaseFormatType) -1;

    _validName = "undefined-database-format";
    _invalidName = "database-format-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(DataBaseFormatMapperTest)
