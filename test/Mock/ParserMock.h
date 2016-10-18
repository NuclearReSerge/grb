#include "Tools/Parser.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class ParserMock : public Parser
{
public:
  ParserMock()
    : Parser()
  {
  }

  MOCK_METHOD0(parse, bool());
};

} // namespace grb

