#pragma once

#include "Correlation/Correlation.h"

#include <gmock/gmock.h>

namespace grb
{

class CorrelationMock : public Correlation
{
public:
  CorrelationMock(const type::CorrelationType type)
    : Correlation(type)
  {
  }

  MOCK_METHOD2(doParse, bool(type::CorrelationCmdType cmd, std::list<std::string>& tokens));
  MOCK_METHOD1(doExecute, void(type::CorrelationCmdType cmd));
  MOCK_METHOD0(doHelp, std::string());
  MOCK_METHOD2(doGenerate, void(Catalog& catalogData, Catalog& catalogModel));

  bool setXAxis(type::Float range, std::size_t points)
  {
    return Correlation::setXAxis(range, points);
  }
  bool setYAxis(type::Float range, std::size_t points)
  {
    return Correlation::setYAxis(range, points);
  }
};

} // namespace grb
