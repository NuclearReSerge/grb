#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class CmdCorrelation : public Cmd
{
public:
  CmdCorrelation(CommandLine& cli);

protected:
  bool doParse(std::list<std::string>& tokens);
  void doExecute();
  std::string doHelp(type::HelpType type);
};

}
