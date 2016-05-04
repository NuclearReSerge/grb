#include "Tools/NameMapper.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class ObservatoryType : public NameMapper
{
protected:
  friend class Singleton<ObservatoryType>;

  ObservatoryType();
  const std::vector<std::string>& getList() const;
};

typedef Singleton<ObservatoryType> Observatory;
}
