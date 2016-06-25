#include "CLI/Cmd.h"
#include "Common/Global.h"

#pragma once

namespace grb
{

class ModelBase;

class CmdModel : public Cmd
{
public:
  CmdModel(CommandLine& cli);

protected:
  bool doParse(std::list<std::string>& args);
  void doExecute();
  std::string doHelp(type::HelpType type);

  void modelNameMapping(const std::string& name);
};

}
