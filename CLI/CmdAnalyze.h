#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class CmdAnalyze : public Cmd
{
public:
  CmdAnalyze(CommandLine& cli);

  bool parse(std::list<std::string>& args) throw(Exception);

protected:
  std::string doHelp(type::HelpType type);
  void doExecute(Analyzer*& analyzer);

private:
  std::string _subcommand;
};

}
