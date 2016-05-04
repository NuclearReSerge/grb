#include "Analyzer/CorrelationTimeArcGrbcat.h"
#include "Common/Global.h"
#include "Data/Catalog.h"
#include "Data/CatalogEntryGrbcat.h"

#include "Common/trace.h"

namespace grb
{

CorrelationTimeArcGrbcat::CorrelationTimeArcGrbcat()
  : Correlation(type::TIME_DIFF_VS_CIRCLE_DIST_GRBCAT)
{
}

CorrelationTimeArcGrbcat::~CorrelationTimeArcGrbcat()
{
  _entries.clear();
}

bool
CorrelationTimeArcGrbcat::buildCF(const Catalog& catalog)
{
  if (!checkCatalog(catalog))
  {
    return false;
  }
  filterEntries(catalog);

  TRACE("ENTRIES " << _entries.size());

  return true;
}

bool
CorrelationTimeArcGrbcat::checkCatalog(const Catalog& catalog)
{
  if (catalog.getType() != type::GRBCAT)
  {
    return false;
  }

  CatalogEntryGRBCAT* entry = dynamic_cast<CatalogEntryGRBCAT*>(*catalog.begin());
  if (!entry)
  {
    return false;
  }

  return true;
}

void
CorrelationTimeArcGrbcat::filterEntries(const Catalog& catalog)
{
  for (const CatalogEntry* entry : catalog)
  {
    const CatalogEntryGRBCAT* entryGrbcat = static_cast<const CatalogEntryGRBCAT*>(entry);
    if (entryGrbcat->getCoodinates().getType() == type::J2000 &&
        entryGrbcat->getCoodinates().getCoordFlag() != -1 &&
        entryGrbcat->getTime().getType() == type::MODIFIED_JULIAN_DATE &&
        entryGrbcat->getTime().getTimeMJD() != 0.0)
    {
      _entries.push_back(entryGrbcat);
    }
  }
}

}
