#include "Analyzer/AnalyzerMapper.h"

namespace grb
{

namespace
{

const std::vector<std::string> ANALYSER_NAMES
{
  "grbcat-analyzer",

  // LAST
  "undefined-analyzer"
};

}

namespace mapper
{

AnalyzerMapper::AnalyzerMapper()
{
  initiate();
}

const std::vector<std::string>& AnalyzerMapper::getList() const
{
  return ANALYSER_NAMES;
}

}

}
