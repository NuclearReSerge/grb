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
    _what = Exception::getPrefix();
  }
  void TearDown()
  {
    std::cout << _what << std::endl;
  }

  std::string _what;
};

TEST_F(ExceptionTest, no_Message_no_Function)
{
  Exception exc;
  ASSERT_STREQ(_what.c_str(), exc.what());
}

TEST_F(ExceptionTest, Message_no_Function)
{
  _what += MESSAGE;

  Exception exc(MESSAGE);
  ASSERT_STREQ(_what.c_str(), exc.what());
}

TEST_F(ExceptionTest, Message_Function)
{
  std::string func(__PRETTY_FUNCTION__);
  _what += "[" + func + "] " + MESSAGE;

  Exception exc(MESSAGE, func);
  ASSERT_STREQ(_what.c_str(), exc.what());
}

}
}
