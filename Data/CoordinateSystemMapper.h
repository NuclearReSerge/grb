#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum CoordinateSystemType
{
  // math
  CARTESIAN,
  CYLINDRICAL,
  SPHERICAL,
  // astronomy
  EQUATORIAL_B1950,
  EQUATORIAL_J2000,
  ECLIPTIC,
  GALACTIC,

  // LAST
  UNDEFINED_COORDINATE_SYSTEM
};

}

namespace mapper
{

class CoordinateSystemMapper : public Mapper<type::CoordinateSystemType>
{
public:
  CoordinateSystemMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::CoordinateSystemMapper> CoordinateSystemMapper;

}

