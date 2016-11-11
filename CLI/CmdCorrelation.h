#pragma once

#include "CLI/Cmd.h"
#include "Correlation/CorrelationCmdType.h"
#include "Correlation/CorrelationType.h"

namespace grb
{

typedef Cmd<type::CorrelationType, type::CorrelationCmdType> CmdCorrelationBase;

class CmdCorrelation : public CmdCorrelationBase
{
public:
  CmdCorrelation()
    : CmdCorrelationBase(type::CMD_CORRELATION)
  {
  }

protected:
  type::CorrelationType getMappedObjectVal(std::string& objStr) override;
  type::CorrelationCmdType getMappedSubCmdVal(std::string& cmdStr) override;
  std::string getMappedSubCmdStr(type::CorrelationCmdType cmdVal) override;
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
  type::CorrelationCmdType _subCmd;
  type::CorrelationType _type;
};

} // namespace grb
