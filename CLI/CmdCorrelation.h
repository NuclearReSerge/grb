#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class CmdCorrelation : public Cmd
{
public:
  CmdCorrelation();

protected:
  bool doParse(std::list<std::string>& tokens) override;
  void doExecute() override;
  std::string doHelp(const type::CommandHelpType type) override;
};

} // namespace grb
