#include "CLI/CmdMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> COMMAND_NAMES
{
  "exit",
  "quit",
  "help",
  "database",
  "model",
  "filter",
  "correlation",
  "analyzer",

  // LAST
  "undefined-command"
};

}

namespace mapper
{

CmdMapper::CmdMapper()
{
  initiate();
}

const std::vector<std::string>& CmdMapper::getList() const
{
  return COMMAND_NAMES;
}

}

}
