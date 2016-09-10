#include "Common/Global.h"

#pragma once

namespace grb
{
namespace type
{

enum CoordinateIndex
{
  X0,
  X1,
  X2,
  X3,

  NUMBER_OF_COORDINATES
};

struct CommonSystem
{
  type::Float x0;
  type::Float x1;
  type::Float x2;
  type::Float x3;
};

struct CartesianSystem
{
  type::Float t;
  type::Float x;
  type::Float y;
  type::Float z;
};

struct CylindricalSystem
{
  type::Float t;
  type::Float rho;
  type::Float phi;
  type::Float z;
};

struct SphericalSystem
{
  type::Float t;
  type::Float r;
  type::Float phi;
  type::Float theta;
};

struct CelestialSystem
{
  type::Float t;
  type::Float dummy;
  type::Float longitude;
  type::Float latitude;
};

} // namespace type
} // namespace grb
