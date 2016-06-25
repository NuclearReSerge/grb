#include "Analyzer/Correlation.h"
#include "Analyzer/GreatCircleDistance.h"
#include "Common/Global.h"

#include <vector>

#pragma once

namespace grb
{

class CatalogEntry;

class CorrelationTimeArcGrbcat : public Correlation
{
public:
  CorrelationTimeArcGrbcat();
  ~CorrelationTimeArcGrbcat();

  bool buildCF(Catalog& catalog);
  bool saveCF(const std::string& filename);

protected:
  bool checkCatalog(Catalog& catalog);
  void filterEntries(Catalog& catalog, std::vector<CatalogEntry*>& entries);
  void initiate();
  std::size_t generateCF(Catalog& catalog, std::vector< std::vector<std::size_t> > hist);
  void normalize(std::vector< std::vector<type::Float>>& cf, type::Float norm);
private:
  type::ArcFormulaType _formula;

  std::size_t _pairsData;
  std::size_t _pairsModel;
  std::vector< std::vector<type::Float> > _cf;
  std::vector< std::vector<std::size_t> > _histData;
  std::vector< std::vector<std::size_t> > _histModel;
};

}
