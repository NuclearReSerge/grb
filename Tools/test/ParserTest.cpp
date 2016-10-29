#include "Tools/Parser.h"

#include "test/Mock/ParserMock.h"

#include <gmock/gmock.h>

namespace testing
{

class ParserTest : public Test
{
protected:
  grb::ParserMock _parser;

};

TEST_F(ParserTest, init)
{
  ASSERT_EQ(0, _parser.getNumberOfRows());
}

} // namespace testing
