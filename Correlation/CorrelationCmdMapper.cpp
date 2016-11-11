#include "Correlation/CorrelationCmdMapper.h"

namespace
{

const std::vector<std::string> CORRELATION_CMD_NAMES
{
  "create",
  "help",

  "generate",
  "save",

  // TimeArcGrbcat
  "set-x-axis",
  "set-y-axis",
  "set-fileprefix",

  // LAST
  "undefined-correlation-command"
};

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>& CorrelationCmdMapper::getList() const
{
  return CORRELATION_CMD_NAMES;
}

} // namespace mapper
} // namespace grb
