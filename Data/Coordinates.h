#include "Common/Global.h"
#include "Data/CoordinateSystemMapper.h"
#include "Data/DateMapper.h"
#include "Data/UnitMapper.h"

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

}

class Coordinates
{
public:
  Coordinates(type::CoordinateSystemType coorType = type::UNDEFINED_COORDINATE_SYSTEM,
              type::DateType dateType = type::UNDEFINED_DATE);
  virtual ~Coordinates();

  type::CoordinateSystemType getCoorType() const;
  type::DateType getDateType() const;

  /** **********************************************************************************************
   *
   *
   *
   ************************************************************************************************/
  void setUnitType(const type::CoordinateIndex idx, const type::UnitType type);

  type::UnitType getUnitType(const type::CoordinateIndex idx) const;

  /** **********************************************************************************************
   *
   *
   *
   ************************************************************************************************/
  type::Float& getX0();
  type::Float& getX1();
  type::Float& getX2();
  type::Float& getX3();

  /** **********************************************************************************************
   *
   * time
   *
   ************************************************************************************************/
  type::Float getT();
  // system date
  type::Float getTimeUnix();
  // Julian Date
  type::Float getTimeJD();
  type::Float getTimeMJD();
  /** **********************************************************************************************
   *
   * space
   *
   ************************************************************************************************/
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

private:
  type::CoordinateSystemType _coorType;
  type::DateType _dateType;
  type::UnitType _unitTypes[type::NUMBER_OF_COORDINATES];

  union
  {
    type::CommonSystem common;
    type::CartesianSystem cartesian;
    type::CylindricalSystem cylindrical;
    type::SphericalSystem spherical;
    type::CelestialSystem celestial;
  } _u;
};

}
