#pragma once

#include "CLI/Cmd.h"
#include "CLI/CommandMapper.h"
#include "Common/Factory.h"

FACTORY_CLASS_H(CommandFactory, type::CommandType, CmdBase, CommandMapper)
