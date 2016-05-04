#include "Common/Global.h"
#include "Common/Singleton.h"

#include <string>

#pragma once

namespace grb
{

class Analyzer;

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
