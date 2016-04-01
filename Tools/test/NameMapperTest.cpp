#include "Tools/test/NameMapperTest.h"

#include <gmock/gmock.h>

namespace grb
{
namespace test
{

/***************************************************************************************************
 *
 * NameMapperTest
 *
 **************************************************************************************************/

const std::string NameMapperTest::_empty;
const std::string NameMapperTest::_invalid = "INVALID_NAME";

bool
NameMapperTest::tryToGetIndex(const std::string& name)
{
  try
  {
    _mapper->getIndex(name);
  }
  catch (Exception& exc)
  {
    std::cout << exc.what() << std::endl;
    return false;
  }
  return true;
}

bool
NameMapperTest::tryToGetName(const type::Index index)
{
  try
  {
    _mapper->getName(index);
  }
  catch (Exception& exc)
  {
    std::cout << exc.what() << std::endl;
    return false;
  }
  return true;
}

/***************************************************************************************************
 *
 * NameMapperMock
 *
 **************************************************************************************************/

namespace
{
  const NameMapper::VectorString NAME_LIST
  {
    "NAME_LIST_FIRST",
    "NAME_LIST_LAST"
  };

  const std::string DESCRIPTION = "DESCRIPTION";
}

class NameMapperDummy : public NameMapper
{
public:
  NameMapperDummy()
    : NameMapper(type::DUMMY, DESCRIPTION)
  {
    initiate();
  }

protected:
  const NameMapper::VectorString& getNameList() const
  {
    return NAME_LIST;
  }
};

/***************************************************************************************************
 *
 * NameMapper test case
 *
 **************************************************************************************************/

class NameMapperDummyTest : public NameMapperTest
{
  void SetUp()
  {
    _mapper = new NameMapperDummy;
    _columnType = type::DUMMY;
    _firstIdx = 0;
    _lastIdx = 1;
    _first = "NAME_LIST_FIRST";
    _last = "NAME_LIST_LAST";
  }

  void TearDown()
  {
    delete _mapper;
  }
};

NAME_MAPPER_TESTS(NameMapperDummyTest)

}
}
