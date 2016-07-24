#include "Model/ModelCmdMapper.h"

namespace grb
{

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

}

namespace mapper
{

ModelCmdMapper::ModelCmdMapper()
{
  initiate();
}

const std::vector<std::string>& ModelCmdMapper::getList() const
{
  return MODEL_CMD_NAMES;
}

}

}
