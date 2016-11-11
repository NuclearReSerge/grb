#pragma once

#include "Analyzer/AnalyzerType.h"
#include "Analyzer/AnalyzerCmdType.h"
#include "Common/BaseObject.h"

namespace grb
{

typedef BaseObject<type::AnalyzerType, type::AnalyzerCmdType> AnalyzerBase;

class Analyzer : public AnalyzerBase
{
public:

  Analyzer(const type::AnalyzerType type = type::UNDEFINED_ANALYZER)
    : AnalyzerBase(type)
  {
  }

  std::string list()
  {
    return doList();
  }

  virtual bool isConfigurationValid() = 0;

protected:
  bool isCommandValid(const type::AnalyzerCmdType cmd)
  {
    switch (cmd)
    {
      case type::ANALYZER_CREATE:
      case type::ANALYZER_HELP:
      case type::ANALYZER_LIST:
      {
        return false;
      }
      default:
        return true;
    }
  }
  virtual std::string doList() = 0;

};

} // namespace grb
