#include "Common/Global.h"

#pragma once

namespace grb
{

class Coordinates
{
public:
  Coordinates(type::CoordinateSystemType type = type::COORDINATE_SYSTEM_UNDEFINED);
  virtual ~Coordinates();

  type::CoordinateSystemType getType() const;

  void setX1UnitType(type::UnitType unitType);
  void setX2UnitType(type::UnitType unitType);
  void setX3UnitType(type::UnitType unitType);

  // general
  type::Float& getX1();
  type::Float& getX2();
  type::Float& getX3();

// CartesianSystem
  type::Float getCarX();
  type::Float getCarY();
  type::Float getCarZ();
// CylindricalSystem
  type::Float getCylRho();
  type::Float getCylPhi();
  type::Float getCylZ();
// SphericalSystem
  type::Float getSphR();
  type::Float getSphPhi();
  type::Float getSphTheta();
// CelestialSystem
  // equinox J2000
  type::Float getCelRightAscension();
  type::Float getCelDeclination();
  // galactic
  type::Float getCelLongnitude();
  type::Float getCelLatitude();

  virtual bool isValid();

protected:
  enum CoordinateIndex
  {
    X1,
    X2,
    X3
  };

  struct CommonSystem
  {
    type::Float x1;
    type::Float x2;
    type::Float x3;
  };

  struct CartesianSystem
  {
    type::Float x;
    type::Float y;
    type::Float z;
  };

  struct CylindricalSystem
  {
    type::Float rho;
    type::Float phi;
    type::Float z;
  };

  struct SphericalSystem
  {
    type::Float r;
    type::Float phi;
    type::Float theta;
  };

  struct CelestialSystem
  {
    type::Float dummy;
    type::Float longitude;
    type::Float latitude;
  };

  void conversionMapper(type::CoordinateSystemType targetSys, CoordinateIndex index);

  typedef type::Float (Coordinates::*fPtr)(const CommonSystem& sys) const;

  fPtr _convert;

  type::Float identity(const CommonSystem& sys) const;

  type::Float convCarCylX1(const CommonSystem& sys) const;
  type::Float convCarCylX2(const CommonSystem& sys) const;
  type::Float convCarCylX3(const CommonSystem& sys) const;

  type::Float convCarSphX1(const CommonSystem& sys) const;
  type::Float convCarSphX2(const CommonSystem& sys) const;
  type::Float convCarSphX3(const CommonSystem& sys) const;

  type::Float convCylCarX1(const CommonSystem& sys) const;
  type::Float convCylCarX2(const CommonSystem& sys) const;
  type::Float convCylCarX3(const CommonSystem& sys) const;

  type::Float convCylSphX1(const CommonSystem& sys) const;
  type::Float convCylSphX2(const CommonSystem& sys) const;
  type::Float convCylSphX3(const CommonSystem& sys) const;

  type::Float convSphCarX1(const CommonSystem& sys) const;
  type::Float convSphCarX2(const CommonSystem& sys) const;
  type::Float convSphCarX3(const CommonSystem& sys) const;

  type::Float convSphCylX1(const CommonSystem& sys) const;
  type::Float convSphCylX2(const CommonSystem& sys) const;
  type::Float convSphCylX3(const CommonSystem& sys) const;


private:
  type::CoordinateSystemType _type;
  union
  {
    CommonSystem common;
    CartesianSystem cartesian;
    CylindricalSystem cylindrical;
    SphericalSystem spherical;
    CelestialSystem celestial;
  } _u;

  type::UnitType _x1Type;
  type::UnitType _x2Type;
  type::UnitType _x3Type;

  fPtr _map[type::COORDINATE_SYSTEM_UNDEFINED];
};

}
