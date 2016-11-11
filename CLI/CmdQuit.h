#pragma once

#include "CLI/Cmd.h"

namespace grb
{

class CmdQuit : public CmdBase
{
public:
  CmdQuit(type::CommandType cmdType = type::CMD_QUIT)
    : CmdBase(cmdType)
  {
  }

  virtual bool parse(std::list<std::string>& tokens) override;
  virtual void execute() override;
  virtual std::string help(type::CommandHelpType type = type::HELP_SHORT) override;
};

} // namespace grb
