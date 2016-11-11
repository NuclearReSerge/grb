#include "Database/DatabaseCmdMapper.h"

namespace
{

const std::vector<std::string> DATABASE_CMD_NAMES
{
  "create",
  "help",

  // LAST
  "undefined-database-command"
};

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>& DatabaseCmdMapper::getList() const
{
  return DATABASE_CMD_NAMES;
}

} // namespace mapper
} // namespace grb
