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
  std::vector<std::string>& getNameList() const;
};

typedef Singleton<ObservatoryType> Observatory;
}
