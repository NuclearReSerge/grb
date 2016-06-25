#include "Data/Coordinates.h"

namespace grb
{

Coordinates::Coordinates(type::CoordinateSystemType type)
  : _type(type),
    _x1Type(type::UNIT_TYPE_UNDEFINED),
    _x2Type(type::UNIT_TYPE_UNDEFINED),
    _x3Type(type::UNIT_TYPE_UNDEFINED)
{
  _u.common.x1 = 0.0;
  _u.common.x2 = 0.0;
  _u.common.x3 = 0.0;
}

Coordinates::~Coordinates()
{

}

type::CoordinateSystemType
Coordinates::getType() const
{
  return _type;
}

void
Coordinates::setX1UnitType(type::UnitType unitType)
{
  _x1Type = unitType;
}

void
Coordinates::setX2UnitType(type::UnitType unitType)
{
  _x2Type = unitType;
}

void
Coordinates::setX3UnitType(type::UnitType unitType)
{
  _x3Type = unitType;
}


/** ***********************************************************************************************/

type::Float&
Coordinates::getX1()
{
  return _u.common.x1;
}

type::Float&
Coordinates::getX2()
{
  return _u.common.x2;
}

type::Float&
Coordinates::getX3()
{
  return _u.common.x3;
}

/** ***********************************************************************************************/

type::Float
Coordinates::getCarX()
{
  return _u.cartesian.x;
}

type::Float
Coordinates::getCarY()
{
  return _u.cartesian.y;
}

type::Float
Coordinates::getCarZ()
{
  return _u.cartesian.z;
}

/** ***********************************************************************************************/

type::Float
Coordinates::getCylRho()
{
  return _u.cylindrical.rho;
}

type::Float
Coordinates::getCylPhi()
{
  return _u.cylindrical.phi;
}

type::Float
Coordinates::getCylZ()
{
  return _u.cylindrical.rho;
}

/** ***********************************************************************************************/

type::Float
Coordinates::getSphR()
{
  return _u.spherical.r;
}

type::Float
Coordinates::getSphPhi()
{
  return _u.spherical.phi;
}

type::Float
Coordinates::getSphTheta()
{
  return _u.spherical.theta;
}

/** ***********************************************************************************************/

type::Float
Coordinates::getCelRightAscension()
{
  return _u.celestial.longitude;
}

type::Float
Coordinates::getCelDeclination()
{
  return _u.celestial.latitude;
}

/** ***********************************************************************************************/

type::Float
Coordinates::getCelLongnitude()
{
  return _u.celestial.longitude;
}

type::Float
Coordinates::getCelLatitude()
{
  return _u.celestial.latitude;
}

/** ***********************************************************************************************/

bool
Coordinates::isValid()
{
  return true;
}

}
