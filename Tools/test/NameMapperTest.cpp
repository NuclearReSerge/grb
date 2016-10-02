#include "test/Mock/NameMapperMock.h"
#include "test/Mock/NameMapperTestFixtures.h"

namespace
{

const std::vector<std::string> NAMES
{
  "undefined-column",

  //
  "column"
};

const std::string DESC { "description" };

} // namespace

namespace testing
{

class NameMapperMapperTest : public NameMapperTestFixturesBase<grb::mapper::NameMapperMock>
{
protected:
  void SetUp()
  {
    EXPECT_CALL(_nameMapper, getList())
        .WillOnce(ReturnRef(NAMES));

    EXPECT_CALL(_nameMapper, getDescription())
        .WillRepeatedly(ReturnRef(DESC));

    _nameMapper.initiateMock();

    _columnType = grb::type::UNDEFINED_COLUMN;
    _validValue = 0;
    _invalidValue = -1;
    _validKey = "undefined-column";
    _invalidKey = "invalid-column";
  }
};

} // namespace testing

NAME_MAPPER_TEST_FIXTURES(NameMapperMapperTest)
