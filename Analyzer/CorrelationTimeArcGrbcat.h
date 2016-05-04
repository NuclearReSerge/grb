#include "Analyzer/Correlation.h"

#include <vector>

#pragma once

namespace grb
{

class CatalogEntryGRBCAT;

class CorrelationTimeArcGrbcat : public Correlation
{
public:
  CorrelationTimeArcGrbcat();
  ~CorrelationTimeArcGrbcat();

  bool buildCF(const Catalog& catalog);

protected:
  bool checkCatalog(const Catalog& catalog);

  void filterEntries(const Catalog& catalog);

private:
  std::vector<const CatalogEntryGRBCAT*> _entries;

};

}
