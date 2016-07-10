#include "Analyzer/Analyzer.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

namespace factory
{

class AnalyzerFactory
{
public:
  virtual Analyzer* create(type::AnalyzerType type);
  virtual Analyzer* create(const std::string& name);
};

}

typedef Singleton<factory::AnalyzerFactory> AnalyzerFactory;

}
