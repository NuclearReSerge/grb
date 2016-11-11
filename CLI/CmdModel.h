#pragma once

#include "CLI/Cmd.h"
#include "Model/ModelCmdType.h"
#include "Model/ModelType.h"

namespace grb
{

typedef Cmd<type::ModelType, type::ModelCmdType> CmdModelBase;

class CmdModel : public CmdModelBase
{
public:
  CmdModel()
    : CmdModelBase(type::CMD_MODEL)
  {
  }

protected:
  type::ModelType getMappedObjectVal(std::string& objStr) override;
  type::ModelCmdType getMappedSubCmdVal(std::string& cmdStr) override;
  std::string getMappedSubCmdStr(type::ModelCmdType cmdVal) override;
  bool isObjectCreated() override;
  std::string getCreatedObjectName() override;
  bool doParse(std::list<std::string>& tokens) override;
  void doExecute() override;
  std::string doHelp(type::CommandHelpType type) override;
  void executeCreate() override;
  void executeHelp() override;

  bool parseGenerate(std::list<std::string>& tokens);
  void executeGenerate();

private:
  type::ModelCmdType _subCmd;
  type::ModelType _type;
};

} // namespace grb
