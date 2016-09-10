#include "Data/Coordinates.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class CoordinatesMock : public Coordinates
{
public:
  CoordinatesMock(type::CoordinateSystemType type = type::UNDEFINED_COORDINATE_SYSTEM)
    : Coordinates(type)
  {
  }

protected:
  MOCK_METHOD0(isValid, bool());
};

} // namespace grb
