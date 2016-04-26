#include "test/Mock/CoordinatesMock.h"

namespace grb
{
namespace test
{

CoordinatesMock::CoordinatesMock(type::CoordinateSystemType type)
  : Coordinates(type)
{
}

type::Float&
CoordinatesMock::getCoordFlag()
{
  return Coordinates::getCoordFlag();
}

type::Float&
CoordinatesMock::getHorizontal()
{
  return Coordinates::getHorizontal();
}

type::Float&
CoordinatesMock::getVertical()
{
  return Coordinates::getVertical();
}

void
CoordinatesMock::setHorizontalUnitType(type::UnitType unitType)
{
  Coordinates::setHorizontalUnitType(unitType);
}

void
CoordinatesMock::setVerticalUnitType(type::UnitType unitType)
{
  Coordinates::setVerticalUnitType(unitType);
}

}
}
