#include "Common/Global.h"
#include "Data/ColumnType.h"

//#include "test/Mock/NameMapperMock.h"
//#include "test/Mock/MapperTestFixtures.h"
#include "test/Mock/MockHelper.h"

#include <gmock/gmock.h>

#pragma once

namespace testing
{

template <typename N>
class NameMapperTestFixturesBase : public Test
{
protected:
  grb::type::Index callGetValue(const std::string& key)
  {
    try
    {
      return _nameMapper.getValue(key);
    }
    catch (grb::Exception& exc)
    {
      printWhat(exc);
      _thrown = true;
    }
    return -1;
  }

  std::string callGetKey(const grb::type::Index value)
  {
    try
    {
      return _nameMapper.getKey(value);
    }
    catch (grb::Exception& exc)
    {
      printWhat(exc);
      _thrown = true;
    }
    return "";
  }

  grb::type::Index callGetIndex(const std::string& key)
  {
    try
    {
      return _nameMapper.getIndex(key);
    }
    catch (grb::Exception& exc)
    {
      printWhat(exc);
      _thrown = true;
    }
    return -1;
  }

  std::string callGetName(const grb::type::Index value)
  {
    try
    {
      return _nameMapper.getName(value);
    }
    catch (grb::Exception& exc)
    {
      printWhat(exc);
      _thrown = true;
    }
    return "";
  }


  bool _thrown { false };

  grb::type::Index _validValue;
  grb::type::Index _invalidValue;
  std::string _validKey;
  std::string _invalidKey;

  grb::type::ColumnType _columnType;
  N _nameMapper;
};

} // namespace testing

#define NAME_MAPPER_TEST_FIXTURES(_NAME_MAPPER_TEST_NAME_)\
namespace testing\
{\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, getColumnType)\
{\
  ASSERT_EQ(_columnType, _nameMapper.getColumnType());\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, getDescription)\
{\
  ASSERT_FALSE(_nameMapper.getDescription().empty());\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, isPresent_Positive)\
{\
  ASSERT_TRUE(_nameMapper.isPresent(_validKey));\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, isPresent_Negative)\
{\
  ASSERT_FALSE(_nameMapper.isPresent(_invalidKey));\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, getValue_Positive)\
{\
  ASSERT_EQ(_validValue, callGetValue(_validKey));\
  ASSERT_FALSE(_thrown);\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, getValue_Negative)\
{\
  callGetValue(_invalidKey);\
  ASSERT_TRUE(_thrown);\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, getKey_Positive)\
{\
  ASSERT_STREQ(_validKey.c_str(), callGetKey(_validValue).c_str());\
  ASSERT_FALSE(_thrown);\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, getKey_Negative)\
{\
  callGetKey(_invalidValue);\
  ASSERT_TRUE(_thrown);\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, getIndex_Positive)\
{\
  ASSERT_EQ(_validValue, callGetIndex(_validKey));\
  ASSERT_FALSE(_thrown);\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, getIndex_Negative)\
{\
  callGetIndex(_invalidKey);\
  ASSERT_TRUE(_thrown);\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, getName_Positive)\
{\
  ASSERT_STREQ(_validKey.c_str(), callGetName(_validValue).c_str());\
  ASSERT_FALSE(_thrown);\
}\
\
TEST_F(_NAME_MAPPER_TEST_NAME_, getName_Negative)\
{\
  callGetName(_invalidValue);\
  ASSERT_TRUE(_thrown);\
}\
\
} // namespace testing
