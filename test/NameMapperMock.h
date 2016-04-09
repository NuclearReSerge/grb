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
  const NameMapper::VectorString& getNameList() const;
};

}
}
