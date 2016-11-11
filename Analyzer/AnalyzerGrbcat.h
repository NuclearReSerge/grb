#pragma once

#include "Analyzer/Analyzer.h"
#include "Catalog/CatalogType.h"
#include "Common/Global.h"
#include "Correlation/CorrelationType.h"

#include <string>
#include <list>

namespace grb
{

class Correlation;

class AnalyzerGrbcat : public Analyzer
{
public:
  AnalyzerGrbcat();
  ~AnalyzerGrbcat() = default;

  bool isConfigurationValid() override;

protected:
  virtual bool doParse(type::AnalyzerCmdType cmd, std::list<std::string>& tokens) override;
  virtual void doExecute(type::AnalyzerCmdType cmd) override;
  virtual std::string doList() override;
  virtual std::string doHelp() override;

  void checkAnalyzerDataIsValid();

private:

};

} // namespace grb
