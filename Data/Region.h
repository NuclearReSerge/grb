#include "Tools/NameMapper.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class RegionType : public NameMapper
{
protected:
  friend class Singleton<RegionType>;

  RegionType();
  const std::vector<std::string>& getNameList() const;
};

typedef Singleton<RegionType> Region;
}
