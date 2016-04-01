#include "Common/Singleton.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

class TestClass
{
public:
  TestClass()
    : _test(0)
  {
  }

  int get() const
  {
    return _test;
  }

  void set(const int test)
  {
    _test = test;
  }

private:
  int _test;
};

class SingletonTest : public Test
{
};

TEST_F(SingletonTest, instance_BasicType)
{
  ASSERT_NE(nullptr, Singleton<int>::instance());
}

TEST_F(SingletonTest, instance_StdClassType)
{
  ASSERT_NE(nullptr, Singleton<std::string>::instance());
}

TEST_F(SingletonTest, instance_UserType)
{
  ASSERT_NE(nullptr, Singleton<TestClass>::instance());
  ASSERT_EQ((int) 0, Singleton<TestClass>::instance()->get());
  Singleton<TestClass>::instance()->set(-1);
  ASSERT_EQ((int) -1, Singleton<TestClass>::instance()->get());
}

}
}
