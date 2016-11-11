#pragma once

#include "Tools/Parser.h"

#include <gmock/gmock.h>

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

