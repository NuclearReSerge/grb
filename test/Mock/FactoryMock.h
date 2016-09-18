#include "Common/Factory.h"

#include "test/Mock/MapperMock.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{
namespace factory
{

template <typename T, typename U>
class FactoryMock : public Factory<T, U>
{
public:
  FactoryMock(const mapper::MapperMock<U>& map)
    : Factory<T,U>(map)
  {
  }

  MOCK_METHOD1_T(createType, T*(const U& type));
};

} // namespace mapper
} // namespace grb
