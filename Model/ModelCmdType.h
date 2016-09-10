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
}
