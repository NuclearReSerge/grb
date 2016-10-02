#include "CLI/CommandMapper.h"

#include "test/Mock/MapperTestFixtures.h"

namespace testing
{

class CommandMapperTest
    : public MapperTestFixturesBase<grb::type::CommandType, grb::mapper::CommandMapper>
{
protected:
  void SetUp()
  {
    _validType = grb::type::UNDEFINED_COMMAND;
    _invalidType = (grb::type::CommandType) -1;

    _validName = "undefined-command";
    _invalidName = "command-name";
  }
};

} // namespace testing

MAPPER_TEST_FIXTURES(CommandMapperTest)
