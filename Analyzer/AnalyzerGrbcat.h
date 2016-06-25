#include "Analyzer/Analyzer.h"
#include "Common/Global.h"

#include <string>
#include <list>

#pragma once

namespace grb
{

class Correlation;

class AnalyzerGrbcat : public Analyzer
{
public:
  AnalyzerGrbcat();
  ~AnalyzerGrbcat();

  bool parse(std::list<std::string>& subcmd);
  void run();

protected:
  bool cmdCreate(std::string& cfName);
  bool cmdSet();
  bool cmdBuild();
  bool cmdSave();

};

}
