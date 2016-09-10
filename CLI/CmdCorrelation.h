#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class CmdCorrelation : public Cmd
{
public:
  CmdCorrelation();

protected:
  bool doParse(std::list<std::string>& tokens);
  void doExecute();
  std::string doHelp(type::CommandHelpType type);
};

} // namespace grb
