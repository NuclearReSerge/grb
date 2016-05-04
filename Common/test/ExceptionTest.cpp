#include "Common/Exception.h"

#include <gtest/gtest.h>

using namespace ::testing;

namespace grb
{
namespace test
{

namespace
{
const std::string MESSAGE = "MESSAGE";
}

class ExceptionTest : public Test
{
protected:
  void SetUp()
  {
    _level = type::EXCEPTION_CRITICAL;
    _what = Exception::getPrefix();
  }
  void TearDown()
  {
    std::cout << _what << std::endl;
  }

  type::ExceptionLevel _level;
  std::string _what;
};

TEST_F(ExceptionTest, noLevel_no_Message_no_Function)
{
  _level = type::EXCEPTION_LEVEL_UNKNOWN;

  Exception exc;
  ASSERT_EQ(type::EXCEPTION_MASK, exc.getLevel());
  ASSERT_STREQ("", exc.what());
}

TEST_F(ExceptionTest, Level_noMessage_no_Function)
{
  Exception exc(_level);
  ASSERT_EQ(_level, exc.getLevel());
  ASSERT_STREQ(_what.c_str(), exc.what());
}


TEST_F(ExceptionTest, Level_Message_no_Function)
{
  _what += MESSAGE;

  Exception exc(_level, MESSAGE);
  ASSERT_EQ(_level, exc.getLevel());
  ASSERT_STREQ(_what.c_str(), exc.what());
}

TEST_F(ExceptionTest, Level_Message_Function)
{
  std::string func(__PRETTY_FUNCTION__);
  _what += "[" + func + "] " + MESSAGE;

  Exception exc(_level, MESSAGE, func);
  ASSERT_EQ(_level, exc.getLevel());
  ASSERT_STREQ(_what.c_str(), exc.what());
}

}
}
