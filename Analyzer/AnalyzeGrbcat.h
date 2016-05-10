#include "Analyzer/Analyzer.h"

#include <string>
#include <list>

#pragma once

namespace grb
{

class Correlation;

class AnalyzeGrbcat : public Analyzer
{
public:
  AnalyzeGrbcat();
  ~AnalyzeGrbcat();

  void execute(const std::string& subcommands);

protected:
  void parse();

  void cmdCreateCF();
  void cmdSetupCF();
  void cmdBuildCF();
  void cmdWriteCF();

private:
  std::list<std::string> _subcmd;

  Correlation* _correlation;

};

}
