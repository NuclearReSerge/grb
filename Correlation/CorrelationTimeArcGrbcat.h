#include "Correlation/Correlation.h"
#include "Correlation/GreatCircleDistance.h"
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

  bool parse(std::list<std::string>& tokens) override;
  bool build(Catalog& catalogData, Catalog& catalogModel) override;
  bool save(const std::string& filePrefix) override;

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

} // namespace grb
