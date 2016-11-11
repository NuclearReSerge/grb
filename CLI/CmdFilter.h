#pragma once

#include "CLI/Cmd.h"
#include "Filter/FilterCmdType.h"
#include "Filter/FilterType.h"

namespace grb
{

typedef Cmd<type::FilterType, type::FilterCmdType> CmdFilterBase;

class CmdFilter : public CmdFilterBase
{
public:
  CmdFilter()
    : CmdFilterBase(type::CMD_FILTER)
  {
  }

protected:
  type::FilterType getMappedObjectVal(std::string& objStr) override;
  type::FilterCmdType getMappedSubCmdVal(std::string& cmdStr) override;
  std::string getMappedSubCmdStr(type::FilterCmdType cmdVal) override;
  bool isObjectCreated() override;
  std::string getCreatedObjectName() override;
  bool doParse(std::list<std::string>& tokens) override;
  void doExecute() override;
  std::string doHelp(type::CommandHelpType type) override;
  void executeCreate() override;
  void executeHelp() override;

private:
  type::FilterCmdType _subCmd;
  type::FilterType _type;
};

} // namespace grb
