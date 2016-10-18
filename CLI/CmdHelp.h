#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class CmdHelp : public Cmd
{
public:
  CmdHelp();

  bool showAll() const
  {
    return _showAll;
  }
  std::string getSpecific() const
  {
    return _specific;
  }

protected:
  bool doParse(std::list<std::string>& tokens);
  void doExecute();
  std::string doHelp(type::CommandHelpType type);

private:
  bool _showAll;
  std::string _specific;
};

} // namespace grb
