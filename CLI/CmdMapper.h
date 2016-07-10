#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum CommandType
{
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

}

namespace mapper
{

class CmdMapper : public Mapper<type::CommandType>
{
public:
  CmdMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::CmdMapper> CmdMapper;


}
