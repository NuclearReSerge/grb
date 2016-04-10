#include "Tools/NameMapper.h"

#pragma once

namespace grb
{
namespace test
{

class NameMapperMock : public NameMapper
{
public:
  NameMapperMock();

protected:
  const std::vector<std::string>& getNameList() const;
};

}
}
