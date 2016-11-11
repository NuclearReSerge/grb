#pragma once

#include "Catalog/Coordinates.h"

#include <gmock/gmock.h>

namespace grb
{

class CoordinatesMock : public Coordinates
{
public:
  CoordinatesMock(const type::CoordinateSystemType coorType, const type::DateType dateType)
    : Coordinates(coorType, dateType)
  {
  }

protected:
  MOCK_METHOD0(isValid, bool());
};

} // namespace grb
