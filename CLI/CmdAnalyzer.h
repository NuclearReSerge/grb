#pragma once

#include "CLI/Cmd.h"

#include "Analyzer/AnalyzerCmdType.h"
#include "Analyzer/AnalyzerType.h"

namespace grb
{

typedef Cmd<type::AnalyzerType, type::AnalyzerCmdType> CmdAnalyzerBase;

class CmdAnalyzer : public CmdAnalyzerBase
{
public:
  CmdAnalyzer()
    : CmdAnalyzerBase(type::CMD_ANALYZER)
  {
  }

protected:
  type::AnalyzerType getMappedObjectVal(std::string& objStr) override;
  type::AnalyzerCmdType getMappedSubCmdVal(std::string& cmdStr) override;
  std::string getMappedSubCmdStr(type::AnalyzerCmdType cmdVal) override;
  bool isObjectCreated() override;
  std::string getCreatedObjectName() override;
  bool doParse(std::list<std::string>& tokens) override;
  void doExecute() override;
  std::string doHelp(type::CommandHelpType type) override;
  void executeCreate() override;
  void executeHelp() override;

  bool parseList(std::list<std::string>& tokens);
  void executeList();

private:
  type::AnalyzerCmdType _subCmd;
  type::AnalyzerType _type;
};

} // namespace grb
