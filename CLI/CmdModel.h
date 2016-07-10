#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class CmdModel : public Cmd
{
public:
  CmdModel(CommandLine& cli);

protected:
  bool doParse(std::list<std::string>& tokens);
  void doExecute();
  std::string doHelp(type::HelpType type);

  void modelNameMapping(const std::string& name);
};

}
