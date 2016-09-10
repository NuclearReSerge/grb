#include "Tools/NameMapper.h"

#include <gtest/gtest.h>

#pragma once

namespace testing
{

class NameMapperTestBase : public Test
{
public:
  bool tryToGetIndex(const std::string& name);
  bool tryToGetName(const grb::type::Index index);

protected:
  grb::mapper::NameMapper* _mapper;

  grb::type::ColumnType _columnType;
  grb::type::Index _firstIdx;
  grb::type::Index _lastIdx;
  std::string _first;
  std::string _last;

  static const std::string _empty;
  static const std::string _invalid;
};

} // namespace testing

#define NAME_MAPPER_TESTS(_TEST_CASE_)\
namespace testing\
{\
TEST_F(_TEST_CASE_, isPresent_Positive)\
{\
  ASSERT_EQ(true, _mapper->isPresent(_first));\
  ASSERT_EQ(true, _mapper->isPresent(_last));\
}\
\
TEST_F(_TEST_CASE_, isPresent_Negative)\
{\
  ASSERT_EQ(false, _mapper->isPresent(_empty));\
  ASSERT_EQ(false, _mapper->isPresent(_invalid));\
}\
\
TEST_F(_TEST_CASE_, getIndex_Positive)\
{\
  ASSERT_EQ(_firstIdx, _mapper->getIndex(_first));\
  ASSERT_EQ(_lastIdx, _mapper->getIndex(_last));\
}\
\
TEST_F(_TEST_CASE_, getIndex_Negative)\
{\
  ASSERT_EQ(false, tryToGetIndex(_empty));\
  ASSERT_EQ(false, tryToGetIndex(_invalid));\
}\
\
TEST_F(_TEST_CASE_, getName_Positive)\
{\
  ASSERT_STREQ(_first.c_str(), _mapper->getName(_firstIdx).c_str());\
  ASSERT_STREQ(_last.c_str(), _mapper->getName(_lastIdx).c_str());\
}\
\
TEST_F(_TEST_CASE_, getName_Negative)\
{\
  ASSERT_EQ(false, tryToGetName(_firstIdx - 1));\
  ASSERT_EQ(false, tryToGetName(_lastIdx + 1));\
}\
\
TEST_F(_TEST_CASE_, getColumnType)\
{\
  ASSERT_EQ(_columnType, _mapper->getColumnType());\
}\
\
TEST_F(_TEST_CASE_, getDescription)\
{\
  ASSERT_EQ(false, _mapper->getDescription().empty());\
}\
}
