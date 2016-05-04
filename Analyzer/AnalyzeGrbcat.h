#include "Analyzer/Analyzer.h"

#pragma once

namespace grb
{

class Correlation;

class AnalyzeGrbcat : public Analyzer
{
public:
  AnalyzeGrbcat();
  ~AnalyzeGrbcat();

  void execute(const std::string& subcommand);

private:
  Correlation* _correlation;

};

}
