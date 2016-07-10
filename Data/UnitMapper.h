#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum UnitType
{
  NO_UNIT,
  DEGREE,
  SECOND,
  UNIT_UNIX,
  UNIT_JD,
  UNIT_MJD,
  KILO_EV,

  // LAST
  UNDEFINED_UNIT
};

}

namespace mapper
{

class UnitMapper : public Mapper<type::UnitType>
{
public:
  UnitMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::UnitMapper> UnitMapper;

}

