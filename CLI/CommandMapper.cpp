#include "CLI/CommandMapper.h"

#include <algorithm>

namespace
{

const std::vector<std::string> COMMAND_NAMES
{
  "",
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

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>&
CommandMapper::getList() const
{
  return COMMAND_NAMES;
}

} // namespace mapper
} // namespace grb

namespace grb
{

size_t
CommandHelper::maxCommandLength()
{
  static size_t len = std::max_element(COMMAND_NAMES.begin(),
                                       --COMMAND_NAMES.end(),
                                       [](const std::string& item1, const std::string& item2)
                                       { return item1.size() < item2.size(); })->size();
  return len;
}

} // namespace grb
