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

protected:
  MOCK_METHOD0(isValid, bool());
};

}
}
