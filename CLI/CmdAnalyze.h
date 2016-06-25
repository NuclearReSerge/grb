#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class CmdAnalyze : public Cmd
{
public:
  CmdAnalyze(CommandLine& cli);

protected:
  bool doParse(std::list<std::string>& args);
  void doExecute();
  std::string doHelp(type::HelpType type);
};

}
