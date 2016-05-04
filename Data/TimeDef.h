#include "Tools/NameMapper.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class TimeDefType : public NameMapper
{
protected:

  friend class Singleton<TimeDefType>;
  TimeDefType();
  const std::vector<std::string>& getList() const;
};

typedef Singleton<TimeDefType> TimeDef;
}
