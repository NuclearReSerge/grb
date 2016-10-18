#include "Analyzer/Analyzer.h"
#include "Correlation/CorrelationType.h"
#include "Data/CatalogType.h"
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
  ~AnalyzerGrbcat() = default;

protected:
  bool doParse(std::list<std::string>& tokens) override;
  void doExecute() override;

  bool parseCreate(std::list<std::string>& tokens);
  bool parseSet(std::list<std::string>& tokens);
  bool parseBuild();

  void executeCreate();
  void executeSet();
  void executeBuild();
  void executeSave();

  void checkAnalyzerDataIsValid();

private:
  type::CorrelationType _corrType;
  std::string _filePrefix;

};

} // namespace grb
