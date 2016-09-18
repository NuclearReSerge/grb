#include "CLI/Cmd.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class CmdMock : public Cmd
{
public:
  MOCK_METHOD1(doParse, bool(std::list<std::string>& tokens));
  MOCK_METHOD0(doExecute, void());
  MOCK_METHOD1(doHelp, std::string(type::CommandHelpType type));
};

} // namspace grb
