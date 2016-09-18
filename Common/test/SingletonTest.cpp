#include "Common/Singleton.h"

#include <gtest/gtest.h>

namespace
{

class TestClass
{
public:
  TestClass() : _test(0) { }
  int get() const { return _test; }
  void set(const int test) { _test = test; }

private:
  int _test;
};

} // namespace

namespace testing
{

class SingletonTest : public Test
{
};

TEST_F(SingletonTest, instance_BasicType)
{
  ASSERT_NE(nullptr, grb::Singleton<int>::instance());
  ASSERT_EQ((int) 0, *grb::Singleton<int>::instance());
  *grb::Singleton<int>::instance() = -1;
  ASSERT_EQ((int) -1, *grb::Singleton<int>::instance());
}

TEST_F(SingletonTest, instance_StdClassType)
{
  ASSERT_NE(nullptr, grb::Singleton<std::string>::instance());
  ASSERT_STREQ("", grb::Singleton<std::string>::instance()->c_str());
  *grb::Singleton<std::string>::instance() = "string";
  ASSERT_STREQ("string", grb::Singleton<std::string>::instance()->c_str());
}

TEST_F(SingletonTest, instance_UserType)
{
  ASSERT_NE(nullptr, grb::Singleton<TestClass>::instance());
  ASSERT_EQ((int) 0, grb::Singleton<TestClass>::instance()->get());
  grb::Singleton<TestClass>::instance()->set(-1);
  ASSERT_EQ((int) -1, grb::Singleton<TestClass>::instance()->get());
}

} // namespace testing
