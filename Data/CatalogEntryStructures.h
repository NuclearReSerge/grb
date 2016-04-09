#include "Common/Global.h"

#pragma once

namespace grb
{

struct CoordinateSystemUndefined
{
  type::Coordinate horizontal;
  type::Coordinate vertical;
};

struct CoordinateSystemEquinox
{
  type::Coordinate rightAscension;
  type::Coordinate declination;
};

struct CoordinateSystemGalactic
{
  type::Coordinate latitude;
  type::Coordinate longitude;
};

struct Coordinates
{
  type::CoordinateSystemType systemType;
  union
  {
    CoordinateSystemUndefined undefined;
    CoordinateSystemEquinox b1950;
    CoordinateSystemEquinox j2000;
    CoordinateSystemGalactic galactic;
  } u;
  type::Float coord_flag;
};

struct Duration
{
  bool isPresent;
  type::Index mod;
  type::Float value;
  type::Float error;
  type::IntegerRange range;
  type::Integer emin;
  type::Integer emax;
};

struct DurationOther
{
  bool isPresent;
  type::Float value;
  type::String notes;
};

}
