#include "CLI/CmdMapper.h"

#include <algorithm>

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

  _len = std::max_element(COMMAND_NAMES.begin(), --COMMAND_NAMES.end(),
    [](const std::string& item1, const std::string& item2)
    { return item1.size() < item2.size(); })->size();
}

size_t
CmdMapper::maxCmdLength() const
{
  return _len;
}

const std::vector<std::string>& CmdMapper::getList() const
{
  return COMMAND_NAMES;
}

}

}
