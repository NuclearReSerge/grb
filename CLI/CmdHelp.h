#include "CLI/Cmd.h"

#pragma once


namespace grb
{


class CmdHelp : public Cmd
{
public:
  CmdHelp(CommandLine& cli);

protected:
  bool doParse(std::list<std::string>& args);
  void doExecute();
  std::string doHelp(type::HelpType type);

private:
  bool _showAll;
  std::string _specific;
};

}
