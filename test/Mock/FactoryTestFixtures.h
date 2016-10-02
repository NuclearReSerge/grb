#include <gtest/gtest.h>

#pragma once

namespace testing
{

template <typename T, typename P, typename F>
class FactoryTestFixturesBase : public Test
{
protected:
  void TearDown()
  {
    delete _product;
  }

  void callCreateType()
  {
    _product = _factory.createType(_validType);
    ASSERT_NE(nullptr, _product);
    ASSERT_EQ(_validType, _product->getType());
  }

  void callCreateName()
  {
    _product = _factory.createName(_validName);
    ASSERT_NE(nullptr, _product);
    ASSERT_EQ(_validType, _product->getType());
  }

  T _validType;
  T _invalidType;

  std::string _validName;
  std::string _invalidName;

  P* _product { nullptr };
  F _factory;
};

} // namespace testing

#define FACTORY_TEST_FIXTURES(_FACTORY_TEST_NAME_)\
namespace testing\
{\
\
TEST_F(_FACTORY_TEST_NAME_, createType_Negative)\
{\
  _product = _factory.createType(_invalidType);\
  ASSERT_EQ(nullptr, _product);\
}\
\
TEST_F(_FACTORY_TEST_NAME_, createName_Negative)\
{\
  _product = _factory.createName(_invalidName);\
  ASSERT_EQ(nullptr, _product);\
}\
} // namespace testing
