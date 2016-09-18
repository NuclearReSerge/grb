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
  MOCK_CONST_METHOD0(getDescription, const std::string&());

protected:
  MOCK_CONST_METHOD0(getList, std::vector<std::string>&());

};

} // namespace mapper
} // namespace grb
