#include "Data/Coordinates.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class CoordinatesMock : public Coordinates
{
public:
  CoordinatesMock(type::CoordinateSystemType coorType = type::UNDEFINED_COORDINATE_SYSTEM,
                  type::DateType dateType = type::UNDEFINED_DATE)
    : Coordinates(coorType, dateType)
  {
  }

protected:
  MOCK_METHOD0(isValid, bool());
};

} // namespace grb
