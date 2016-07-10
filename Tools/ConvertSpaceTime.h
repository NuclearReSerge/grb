#include "Common/Global.h"
#include "Data/Coordinates.h"
#include "Data/CoordinateSystemMapper.h"

#pragma once

namespace grb
{

class ConvertSpaceTime
{
public:
  ConvertSpaceTime();

  void conversionMapper(type::CoordinateSystemType targetSys, type::CoordinateIndex index);

  typedef type::Float (Coordinates::*fPtr)(const type::CommonSystem& sys) const;

  fPtr _convert;

  type::Float identity(const type::CommonSystem& sys) const;

  type::Float convCarCylX1(const type::CommonSystem& sys) const;
  type::Float convCarCylX2(const type::CommonSystem& sys) const;
  type::Float convCarCylX3(const type::CommonSystem& sys) const;

  type::Float convCarSphX1(const type::CommonSystem& sys) const;
  type::Float convCarSphX2(const type::CommonSystem& sys) const;
  type::Float convCarSphX3(const type::CommonSystem& sys) const;

  type::Float convCylCarX1(const type::CommonSystem& sys) const;
  type::Float convCylCarX2(const type::CommonSystem& sys) const;
  type::Float convCylCarX3(const type::CommonSystem& sys) const;

  type::Float convCylSphX1(const type::CommonSystem& sys) const;
  type::Float convCylSphX2(const type::CommonSystem& sys) const;
  type::Float convCylSphX3(const type::CommonSystem& sys) const;

  type::Float convSphCarX1(const type::CommonSystem& sys) const;
  type::Float convSphCarX2(const type::CommonSystem& sys) const;
  type::Float convSphCarX3(const type::CommonSystem& sys) const;

  type::Float convSphCylX1(const type::CommonSystem& sys) const;
  type::Float convSphCylX2(const type::CommonSystem& sys) const;
  type::Float convSphCylX3(const type::CommonSystem& sys) const;

  type::Float convertJDtoMJD();
  type::Float convertJDtoUNIX();
  type::Float convertMJDtoJD();
  type::Float convertMJDtoUNIX();
  type::Float convertUNIXtoJD();
  type::Float convertUNIXtoMJD();


  fPtr _map[type::UNDEFINED_COORDINATE_SYSTEM];
};

}
