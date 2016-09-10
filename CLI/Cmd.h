#include "CLI/CommandType.h"
#include "Common/Exception.h"

#include <list>
#include <string>

#pragma once

namespace grb
{

class CommandLine;

class Cmd
{
public:
  Cmd() = delete;

  Cmd(type::CommandType cmdType = type::UNDEFINED_COMMAND)
    : _type(cmdType), _cli(nullptr), _wasExecuted(false)
  {
  }

  virtual ~Cmd() = default;

  type::CommandType getType() const
  {
    return _type;
  }

  bool wasExecuted() const
  {
    return _wasExecuted;
  }

  void setCLI(CommandLine* cli)
  {
    _cli = cli;
  }

  bool parse(std::list<std::string>& tokens) throw(Exception);
  void execute();
  std::string help(type::CommandHelpType type = type::HELP_SHORT);

protected:
  virtual bool doParse(std::list<std::string>& tokens) = 0;
  virtual void doExecute() = 0;
  virtual std::string doHelp(type::CommandHelpType type) = 0;

  virtual CommandLine* getCLI()
  {
    return _cli;
  }

private:
  type::CommandType _type;
  CommandLine* _cli;
  bool _wasExecuted;
};

} // namespace grb
