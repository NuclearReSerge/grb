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
  NameMapperMock(const type::ColumnType type = type::UNDEFINED_COLUMN)
    : NameMapper(type)
  {
  }

  void initiateMock()
  {
    NameMapper::initiate();
  }

  MOCK_CONST_METHOD0(getList, const std::vector<std::string>&());
  MOCK_CONST_METHOD0(getDescription, const std::string&());
};

} // namespace mapper
} // namespace grb
