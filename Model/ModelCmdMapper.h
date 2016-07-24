#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum ModelCmdType
{
  // common
  MODEL_CREATE,
  MODEL_GENERATE,
  MODEL_HELP,

  // Isotropic
  MODEL_SET_TIME,
  MODEL_SET_RADIUS,
  MODEL_SET_PHI,
  MODEL_SET_THETA,

  // LAST
  UNDEFINED_MODEL_CMD
};

}

namespace mapper
{

class ModelCmdMapper : public Mapper<type::ModelCmdType>
{
public:
  ModelCmdMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::ModelCmdMapper> ModelCmdMapper;

}

