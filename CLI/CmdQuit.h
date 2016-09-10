#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class CmdQuit : public Cmd
{
public:
  CmdQuit(type::CommandType cmdType = type::CMD_QUIT);

protected:
  bool doParse(std::list<std::string>& tokens);
  void doExecute();
  std::string doHelp(type::CommandHelpType type);
};

} // namespace grb
