#include "Data/Coordinates.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{
namespace test
{

class CoordinatesMock : public Coordinates
{
public:
  CoordinatesMock(type::CoordinateSystemType type = type::COORDINATE_SYSTEM_UNDEFINED);

  type::Float& getCoordFlag();
  type::Float& getHorizontal();
  type::Float& getVertical();

  void setHorizontalUnitType(type::UnitType unitType);
  void setVerticalUnitType(type::UnitType unitType);

protected:
  MOCK_METHOD0(isValid, bool());
};

}
}
