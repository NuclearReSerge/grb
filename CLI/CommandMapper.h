#include "Common/Global.h"
#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

class CommandMapperType : public Mapper<type::CommandType>
{
protected:
  friend class Singleton<CommandMapperType>;
  CommandMapperType();
  const std::vector<std::string>& getList() const;
};

typedef Singleton<CommandMapperType> CommandMapper;


}
