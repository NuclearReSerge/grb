#include "Analyzer/Analyzer.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class AnalyzerMock : public Analyzer
{
public:
  AnalyzerMock()
    : Analyzer()
  {
  }

  MOCK_METHOD1(parse, bool(std::list<std::string>& tokens));
  MOCK_METHOD0(run, void());
};

} // namespace grb
