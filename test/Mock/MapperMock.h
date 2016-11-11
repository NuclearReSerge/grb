#pragma once

#include "Common/Mapper.h"

#include <gmock/gmock.h>

namespace grb
{
namespace mapper
{

template <typename T>
class MapperMock : public Mapper<T>
{
public:
  void initiateMock()
  {
    Mapper<T>::initiate();
  }

  MOCK_CONST_METHOD0_T(getList, const std::vector<std::string>&());
};

} // namespace mapper
} // namespace grb
