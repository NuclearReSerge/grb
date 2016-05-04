#include "CLI/CommandMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> CMD_LIST
{
  "exit",
  "quit",
  "help",
  "database",
  "analyze"
};

}

CommandMapperType::CommandMapperType()
  : Mapper()
{
  initiate();
}

const std::vector<std::string>& CommandMapperType::getList() const
{
  return CMD_LIST;
}

}
