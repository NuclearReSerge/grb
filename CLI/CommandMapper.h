#include "CLI/CommandType.h"
#include "Common/Mapper.h"

#pragma once

MAPPER_CLASS_H(CommandMapper, type::CommandType)

namespace grb
{

class CommandHelper
{
public:
  CommandHelper() = delete;
  static size_t maxCommandLength();
};

} // namespace grb

