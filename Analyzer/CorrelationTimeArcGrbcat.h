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

  bool buildCF(const Catalog& catalog);
  bool saveCF(const std::string& filename);

protected:
  class CoordinatesBkg : public Coordinates
  {
  public:
    CoordinatesBkg(type::Float time, type::Float hori, type::Float vert);
    const type::Float& getTime() const;

  private:
    type::Float _time;
  };

  bool checkCatalog(const Catalog& catalog);
  void filterEntries(const Catalog& catalog, std::vector<const CatalogEntry*>& entries);
  void initiate();


  std::size_t generateCFCAT(const Catalog& catalog);
  std::size_t generateCFBKG(const std::size_t points);
  void generateBackground(std::vector<CoordinatesBkg>& coorVec, std::size_t points);

  void normalize(std::vector< std::vector<type::Float>>& cf, type::Float norm);
private:
  type::ArcFormulaType _formula;

  std::size_t _pairsCfCat;
  std::size_t _pairsCfBkg;
  std::vector< std::vector<type::Float> > _cf;
  std::vector< std::vector<std::size_t> > _cfCat;
  std::vector< std::vector<std::size_t> > _cfBkg;
};

}
