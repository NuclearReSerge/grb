#include "Model/ModelCmdMapper.h"

namespace
{

const std::vector<std::string> MODEL_CMD_NAMES
{
  "create",
  "generate",
  "help",

  // LAST
  "undefined-model-command"
};

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>& ModelCmdMapper::getList() const
{
  return MODEL_CMD_NAMES;
}

} // namespace mapper
} // namespace grb
