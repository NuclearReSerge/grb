#pragma once

#include "CLI/Cmd.h"

#include <gmock/gmock.h>

namespace grb
{

class CmdMock : public CmdBase
{
public:
  CmdMock(const type::CommandType type)
    : CmdBase(type)
  {
  }

  MOCK_METHOD1(parse, bool(std::list<std::string>& tokens));
  MOCK_METHOD0(execute, void());
  MOCK_METHOD1(help, std::string(type::CommandHelpType type));
};

} // namspace grb
