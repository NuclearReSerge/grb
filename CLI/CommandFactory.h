#include "CLI/Cmd.h"
#include "CLI/CommandMapper.h"
#include "Common/Factory.h"

#pragma once

FACTORY_CLASS_H(CommandFactory, type::CommandType, Cmd, CommandMapper)
