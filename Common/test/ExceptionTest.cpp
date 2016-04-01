#include "Common/Exception.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace grb
{
namespace test
{

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
  const Exception exc;
  ASSERT_STREQ(_what.c_str(), exc.what());
}

TEST_F(ExceptionTest, Message_no_Function)
{
  std::string mess("MESSAGE");
  _what += mess;

  const Exception exc(mess);
  ASSERT_STREQ(_what.c_str(), exc.what());
}

TEST_F(ExceptionTest, Message_Function)
{
  std::string mess("MESSAGE");
  std::string func(__PRETTY_FUNCTION__);
  _what += "[" + func + "] " + mess;

  const Exception exc(mess, func);
  ASSERT_STREQ(_what.c_str(), exc.what());
}

} // namespace test
} // namespace grb
