#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class Analyzer;

class CmdAnalyzer : public Cmd
{
public:
  CmdAnalyzer();

protected:
  bool doParse(std::list<std::string>& tokens) override;
  void doExecute() override;
  std::string doHelp(const type::CommandHelpType type) override;

  virtual Analyzer* createAnalyzer(const std::string& name);
};

} // namespace grb
