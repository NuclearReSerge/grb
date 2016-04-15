#include "Coordinates.h"

namespace grb
{

Coordinates::Coordinates(type::CoordinateSystemType type)
  : _type(type), _coord_flag(0.0), _horizontal(0.0), _vertical(0.0),
    _horizontalUnitType(type::UNIT_TYPE_UNDEFINED), _verticalUnitType(type::UNIT_TYPE_UNDEFINED)
{
}

type::CoordinateSystemType
Coordinates::getType() const
{
  return _type;
}

const type::Float&
Coordinates::getCoordFlag() const
{
  return _coord_flag;
}

const type::Float&
Coordinates::getHorizontal() const
{
  return _horizontal;
}

const type::Float&
Coordinates::getVertical() const
{
  return _vertical;
}

const type::Float&
Coordinates::getRightAscension() const
{
  return _horizontal;
}

const type::Float&
Coordinates::getDeclination() const
{
  return _vertical;
}

const type::Float&
Coordinates::getLongnitude() const
{
  return _horizontal;
}

const type::Float&
Coordinates::getLatitude() const
{
  return _vertical;
}

type::Float&
Coordinates::getCoordFlag()
{
  return _coord_flag;
}

type::Float&
Coordinates::getHorizontal()
{
  return _horizontal;
}

type::Float&
Coordinates::getVertical()
{
  return _vertical;
}

void
Coordinates::setHorizontalUnitType(type::UnitType unitType)
{
  _horizontalUnitType = unitType;
}

void
Coordinates::setVerticalUnitType(type::UnitType unitType)
{
  _verticalUnitType = unitType;
}

bool
Coordinates::isValid()
{
  return true;
}

}
