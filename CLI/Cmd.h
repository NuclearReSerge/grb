#include "Common/Exception.h"
#include "CLI/CmdMapper.h"
//#include "Common/Global.h"

#include <list>
#include <string>

#pragma once

namespace grb
{

namespace type
{

enum HelpType
{
  HELP_SHORT,
  HELP_LONG,
  HELP_FULL
};

}

class CommandLine;

class Cmd
{
public:
  Cmd() = delete;
  Cmd(CommandLine& cli, type::CommandType cmdType = type::UNDEFINED_COMMAND);
  virtual ~Cmd();

  type::CommandType getType() const;

  bool parse(std::list<std::string>& tokens) throw(Exception);
  void execute();
  std::string help(type::HelpType type = type::HELP_SHORT);

  bool wasExecuted() const;

protected:
  virtual bool doParse(std::list<std::string>& tokens) = 0;
  virtual void doExecute() = 0;
  virtual std::string doHelp(type::HelpType type) = 0;
  virtual CommandLine& getCLI();

private:
  CommandLine& _cli;
  type::CommandType _type;
  bool _wasExecuted;
};

}
