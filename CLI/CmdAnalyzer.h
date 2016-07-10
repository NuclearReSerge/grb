#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class CmdAnalyzer : public Cmd
{
public:
  CmdAnalyzer(CommandLine& cli);

protected:
  bool doParse(std::list<std::string>& tokens);
  void doExecute();
  std::string doHelp(type::HelpType type);
};

}
