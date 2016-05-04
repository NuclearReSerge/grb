#include <CLI/Cmd.h>

#pragma once


namespace grb
{


class CmdQuit : public Cmd
{
public:
  CmdQuit(CommandLine& cli, type::CommandType cmdType = type::CMD_QUIT);

  bool parse(std::list<std::string>& args) throw(Exception);

protected:
  std::string doHelp(type::HelpType type);
  void doExecute(Analyzer*& analyzer);
};

}
