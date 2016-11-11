#pragma once

#include "Analyzer/Analyzer.h"

#include <gmock/gmock.h>

namespace grb
{

class AnalyzerMock : public Analyzer
{
public:
  AnalyzerMock(const type::AnalyzerType type)
    : Analyzer(type)
  {
  }

  MOCK_METHOD2(doParse, bool(type::AnalyzerCmdType cmd, std::list<std::string>& tokens));
  MOCK_METHOD1(doExecute, void(type::AnalyzerCmdType cmd));
  MOCK_METHOD0(doList, std::string());
  MOCK_METHOD0(doHelp, std::string());

  MOCK_METHOD0(isConfigurationValid, bool());

};

} // namespace grb
