#include "Tools/NameMapper.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class TimeModType : public NameMapper
{
protected:
  TimeModType() = delete;
  TimeModType(const type::ColumnType columnType);
  const  std::vector<std::string>& getList() const;
};

class Time50ModType : public TimeModType
{
protected:
  friend class Singleton<Time50ModType>;
  Time50ModType() : TimeModType(type::T50_MOD)
  {
  }
};

class Time90ModType : public TimeModType
{
protected:
  friend class Singleton<Time90ModType>;
  Time90ModType() : TimeModType(type::T90_MOD)
  {
  }
};

typedef Singleton<Time50ModType> Time50Mod;
typedef Singleton<Time90ModType> Time90Mod;
}
