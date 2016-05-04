#include "Analyzer/Analyzer.h"
#include "Common/Exception.h"
#include "Common/Global.h"

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
  Cmd(CommandLine& cli, type::CommandType cmdType = type::UNKNOWN_COMMAND_NAME);
  virtual ~Cmd();

  type::CommandType getType() const;

  virtual bool parse(std::list<std::string>& args) throw(Exception);

  std::string help(type::HelpType type = type::HELP_SHORT);
  void execute(Analyzer*& analyzer);
  bool wasExecuted() const;

protected:
  virtual std::string doHelp(type::HelpType type) = 0;
  virtual void doExecute(Analyzer*& analyzer) = 0;
  virtual CommandLine& getCLI();

private:
  CommandLine& _cli;
  type::CommandType _type;
  bool _wasExecuted;
};

}
