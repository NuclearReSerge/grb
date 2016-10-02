#include "Common/Exception.h"

#include "test/Mock/MockHelper.h"

#include <gtest/gtest.h>

namespace
{

const std::string MESSAGE = "MESSAGE";

} // namespace

namespace testing
{

class ExceptionTest : public Test
{
protected:
  void SetUp()
  {
    _level = grb::type::EXCEPTION_CRITICAL;
    _what = grb::Exception::getPrefix();
  }

  grb::type::ExceptionLevel _level;
  std::string _what;
};

TEST_F(ExceptionTest, noLevel_no_Message_no_Function)
{
  _level = grb::type::EXCEPTION_LEVEL_UNKNOWN;

  grb::Exception exc;
  ASSERT_EQ(grb::type::EXCEPTION_MASK, exc.getLevel());
  ASSERT_STREQ("", exc.what());
  printWhat(exc);
}

TEST_F(ExceptionTest, Level_noMessage_no_Function)
{
  grb::Exception exc(_level);
  ASSERT_EQ(_level, exc.getLevel());
  ASSERT_STREQ(_what.c_str(), exc.what());
  printWhat(exc);
}

TEST_F(ExceptionTest, Level_Message_no_Function)
{
  _what += MESSAGE;

  grb::Exception exc(_level, MESSAGE);
  ASSERT_EQ(_level, exc.getLevel());
  ASSERT_STREQ(_what.c_str(), exc.what());
  printWhat(exc);
}

TEST_F(ExceptionTest, Level_Message_Function)
{
  std::string func(__PRETTY_FUNCTION__);
  _what += "[" + func + "] " + MESSAGE;

  grb::Exception exc(_level, MESSAGE, func);
  ASSERT_EQ(_level, exc.getLevel());
  ASSERT_STREQ(_what.c_str(), exc.what());
  printWhat(exc);
}

} // namespace testing
