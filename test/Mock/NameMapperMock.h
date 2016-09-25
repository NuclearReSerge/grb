#include "Tools/NameMapper.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{
namespace mapper
{

class NameMapperMock : public NameMapper
{
public:
  NameMapperMock(const type::ColumnType type)
    : NameMapper(type)
  {
  }

  MOCK_CONST_METHOD0(getDescription, const std::string&());
  MOCK_CONST_METHOD0(getList, std::vector<std::string>&());
};

} // namespace mapper
} // namespace grb
