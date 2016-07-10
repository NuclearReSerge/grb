#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum ArcFormulaType
{
  SPHERICAL_LAW_OF_COSINES,
  HAVERSINE_FORMULA,
  VINCENTY_FORMULAE,

  // LAST
  UNDEFINED_ARC_FORMULA
};

}

namespace mapper
{

class ArcFormulaMapper : public Mapper<type::ArcFormulaType>
{
public:
  ArcFormulaMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::ArcFormulaMapper> ArcFormulaMapper;

}
