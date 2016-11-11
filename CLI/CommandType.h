#pragma once

namespace grb
{
namespace type
{

enum CommandType
{
  CMD_UNAVAILABLE,
  CMD_EXIT,
  CMD_QUIT,
  CMD_HELP,
  CMD_DATABASE,
  CMD_MODEL,
  CMD_FILTER,
  CMD_CORRELATION,
  CMD_ANALYZER,

  // LAST
  UNDEFINED_COMMAND
};

enum CmdSubCmdType
{
  CMD_SUBCMD_CREATE,
  CMD_SUBCMD_HELP,
};

enum CommandHelpType
{
  HELP_SHORT,
  HELP_LONG,
  HELP_FULL
};

} // namespace type
} // namespace grb
