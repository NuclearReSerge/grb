#pragma once

#include "CLI/Cmd.h"

namespace grb
{

class CmdHelp : public CmdBase
{
public:
  CmdHelp()
    : CmdBase(type::CMD_HELP), _showAll(true)
  {
  }

  virtual bool parse(std::list<std::string>& tokens) override;
  virtual void execute() override;
  virtual std::string help(type::CommandHelpType type = type::HELP_SHORT) override;

  bool showAll() const
  {
    return _showAll;
  }
  std::string getSpecific() const
  {
    return _specific;
  }

private:
  bool _showAll;
  std::string _specific;
};

} // namespace grb
