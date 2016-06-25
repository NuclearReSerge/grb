#include "CLI/Cmd.h"

#pragma once


namespace grb
{


class CmdQuit : public Cmd
{
public:
  CmdQuit(CommandLine& cli, type::CommandType cmdType = type::CMD_QUIT);

protected:
  bool doParse(std::list<std::string>& args);
  void doExecute();
  std::string doHelp(type::HelpType type);
};

}
