#include "Analyzer/Analyzer.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class AnalyzerMock : public Analyzer
{
public:
  AnalyzerMock(const type::AnalyzerType type)
    : Analyzer(type)
  {
  }

  MOCK_METHOD1(doParse, bool(std::list<std::string>& tokens));
  MOCK_METHOD0(doExecute, void());
};

} // namespace grb
