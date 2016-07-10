#include "CLI/Cmd.h"
#include "Common/Singleton.h"

#include <string>

#pragma once

namespace grb
{

class CommandLine;

namespace factory
{

class CmdFactory
{
public:
  virtual Cmd* create(CommandLine& cli, const type::CommandType type);
  virtual Cmd* create(CommandLine& cli, const std::string& name);
};

}

typedef Singleton<factory::CmdFactory> CmdFactory;

}
