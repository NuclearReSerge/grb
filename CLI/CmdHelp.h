#include <CLI/Cmd.h>

#pragma once


namespace grb
{


class CmdHelp : public Cmd
{
public:
  CmdHelp(CommandLine& cli);

  bool parse(std::list<std::string>& args) throw(Exception);

protected:
  std::string doHelp(type::HelpType type);
  void doExecute(Analyzer& analyzer);

private:
  bool _showAll;
  std::string _specific;
};

}
