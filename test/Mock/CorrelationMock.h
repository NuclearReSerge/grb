#include "Correlation/Correlation.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class CorrelationMock : public Correlation
{
public:
  CorrelationMock(const type::CorrelationType type)
    : Correlation(type)
  {
  }

  MOCK_METHOD1(parse, bool(std::list<std::string>& tokens));
  MOCK_METHOD2(build, bool(Catalog& catalogData, Catalog& catalogModel));
  MOCK_METHOD1(save, bool(const std::string& filePrefix));
};

} // namespace grb
