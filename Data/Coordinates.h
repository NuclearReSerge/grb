#include "Common/Global.h"
#include "Data/CoordinateStructures.h"
#include "Data/CoordinateSystemType.h"
#include "Data/DateType.h"
#include "Data/UnitType.h"

#pragma once

namespace grb
{

class Coordinates
{
public:
  Coordinates(type::CoordinateSystemType coorType = type::UNDEFINED_COORDINATE_SYSTEM,
              type::DateType dateType = type::UNDEFINED_DATE)
    : _coorType(coorType), _dateType(dateType)
  {
    _u.common.x0 = 0.0;
    _u.common.x1 = 0.0;
    _u.common.x2 = 0.0;
    _u.common.x3 = 0.0;

    for (int i = 0; i < type::NUMBER_OF_COORDINATES; ++i)
      _unitTypes[i] = type::UNDEFINED_UNIT;
  }

  virtual ~Coordinates() = default;

  type::CoordinateSystemType getCoorType() const
  {
    return _coorType;
  }

  type::DateType getDateType() const
  {
    return _dateType;
  }

  void setUnitType(const type::CoordinateIndex idx, const type::UnitType type)
  {
    _unitTypes[idx] = type;
  }

  type::UnitType getUnitType(const type::CoordinateIndex idx) const
  {
    return _unitTypes[idx];
  }

  type::Float& getX0()
  {
    return _u.common.x0;
  }

  type::Float& getX1()
  {
    return _u.common.x1;
  }

  type::Float& getX2()
  {
    return _u.common.x2;
  }

  type::Float& getX3()
  {
    return _u.common.x3;
  }

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

} // namespace grb
