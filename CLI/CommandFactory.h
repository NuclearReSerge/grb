#include "Common/Global.h"
#include "Common/Singleton.h"

#include <string>

#pragma once

namespace grb
{

class Cmd;
class CommandLine;

class CommandFactoryType
{
public:
  virtual Cmd* create(CommandLine& cli, const std::string& command);
  virtual Cmd* create(CommandLine& cli, const type::CommandType cmdType);

protected:
  friend class Singleton<CommandFactoryType>;
  CommandFactoryType();
};

typedef Singleton<CommandFactoryType> CommandFactory;

}
