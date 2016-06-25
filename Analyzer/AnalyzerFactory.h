#include "Analyzer/Analyzer.h"
#include "Common/Global.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class AnalyzerFactoryType
{
public:
  virtual Analyzer* create(type::CatalogType catType);

protected:
  friend class Singleton<AnalyzerFactoryType>;
  AnalyzerFactoryType();
};

typedef Singleton<AnalyzerFactoryType> AnalyzerFactory;

}
