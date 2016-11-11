#pragma once

#include "Common/Exception.h"
#include "test/Mock/MockHelper.h"

#include <gtest/gtest.h>

namespace testing
{

template <typename T, typename M>
class MapperTestFixturesBase : public Test
{
protected:
  bool _thrown { false };

  T _validType;
  T _invalidType;

  std::string _validName;
  std::string _invalidName;

  M _mapper;
};

} // namespace testing

#define MAPPER_TEST_FIXTURES(_MAPPER_TEST_NAME_)\
namespace testing\
{\
\
TEST_F(_MAPPER_TEST_NAME_, isPresent_Positive)\
{\
  ASSERT_TRUE(_mapper.isPresent(_validName));\
}\
\
TEST_F(_MAPPER_TEST_NAME_, isPresent_Negative)\
{\
  ASSERT_FALSE(_mapper.isPresent(_invalidName));\
}\
\
TEST_F(_MAPPER_TEST_NAME_, getValue_Positive)\
{\
  ASSERT_EQ(_validType, _mapper.getValue(_validName));\
}\
\
TEST_F(_MAPPER_TEST_NAME_, getValue_Negative)\
{\
  try\
  {\
    _mapper.getValue(_invalidName);\
  }\
  catch (grb::Exception exc)\
  {\
    _thrown = true;\
    printWhat(exc);\
  }\
  ASSERT_TRUE(_thrown);\
}\
\
TEST_F(_MAPPER_TEST_NAME_, getKey_Positive)\
{\
  ASSERT_STREQ(_validName.c_str(), _mapper.getKey(_validType).c_str());\
}\
\
TEST_F(_MAPPER_TEST_NAME_, getKey_Negative)\
{\
  try\
  {\
    _mapper.getKey(_invalidType);\
  }\
  catch (grb::Exception exc)\
  {\
    _thrown = true;\
    printWhat(exc);\
  }\
  ASSERT_TRUE(_thrown);\
}\
\
} // namespace testing
