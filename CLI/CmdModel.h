#include "CLI/Cmd.h"
#include "Model/ModelFactory.h"
#include "Model/ModelCmdMapper.h"

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

  bool parseCreate(std::list<std::string>& tokens);
  bool parseGenerate(std::list<std::string>& tokens);
  bool parseHelp(std::list<std::string>& tokens);

  void executeCreate();
  void executeGenerate();
  void executeHelp();

private:
  type::ModelCmdType _subCmd;
  type::ModelType _modelType;
};

}
