#include "Correlation/CorrelationTimeArcGrbcat.h"

#include "Catalog/Catalog.h"
#include "Catalog/CatalogEntryGrbcat.h"
#include "Common/Exception.h"
#include "Common/Global.h"
#include "Correlation/GreatCircleDistance.h"
#include "Main/AnalysisData.h"
#include "Model/IsotropicSphereModel.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>

#include <sstream>

#include "Common/trace.h"

namespace grb
{

namespace
{

type::Float getTime(const CatalogEntry* entry)
{
  return static_cast<const CatalogEntryGrbcat*>(entry)->getCoodinates().getTimeMJD();
}

class CompareTime
{
public:
  bool operator()(const CatalogEntry* a, const CatalogEntry* b) const
  {
    return getTime(a) < getTime(b);
  }
};

} // namespace


CorrelationTimeArcGrbcat::CorrelationTimeArcGrbcat()
  : Correlation(type::CORRELATION_GRBCAT_DTDARC), _formula(type::VINCENTY_FORMULAE),
    _pairsData(0), _pairsModel(0)
{
}

CorrelationTimeArcGrbcat::~CorrelationTimeArcGrbcat()
{
  for (std::vector<type::Float>& vecValue : _cf)
  {
    vecValue.clear();
  }
  _cf.clear();

  for (std::vector<std::size_t>& vecValue : _histData)
  {
    vecValue.clear();
  }
  _histData.clear();

  for (std::vector<std::size_t>& vecValue : _histModel)
  {
    vecValue.clear();
  }
  _histModel.clear();

}

bool
CorrelationTimeArcGrbcat::doParse(type::CorrelationCmdType cmd, std::list<std::string>& tokens)
{
  switch (cmd)
  {
    default:
      break;
  }

  tokens.clear();

  const Catalog* catalog = AnalysisData::instance()->getCatalogData();

  auto minEntry = std::min_element(catalog->getEntries().begin(), catalog->getEntries().end(),
                                   CompareTime());
  auto maxEntry = std::max_element(catalog->getEntries().begin(), catalog->getEntries().end(),
                                   CompareTime());

  type::Float range = std::ceil((getTime(*maxEntry) - getTime(*minEntry)) / 365.0) * 365.0;

  if (setXAxis(range, 365))
  {
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  "CorrelationTimeArcGrbcat failed to set correlation x axis.\n");
    throw exc;
  }
  setYAxis(M_PIl, 180);

  return true;
}

void
CorrelationTimeArcGrbcat::doExecute(type::CorrelationCmdType cmd)
{
  switch (cmd)
  {
    default:
      break;
  }
}

std::string
CorrelationTimeArcGrbcat::doHelp()
{
  return "CorrelationTimeArcGrbcat::doHelp";
}

void
CorrelationTimeArcGrbcat::doGenerate(Catalog& catalogData, Catalog& catalogModel)
{
  initiate();

  TRACE("GENERATING DATA HISTOGRAM");
  _pairsData = generateCF(catalogData, _histData);
  TRACE("GENERATING MODEL HISTOGRAM");
  _pairsModel = generateCF(catalogModel, _histModel);

  TRACE("PAIRS: DATA = " << _pairsData << ", MODEL = " << _pairsModel);

  for (std::size_t i = 0; i < getYPoints(); ++i)
  {
    for (std::size_t j = 0; j < getXPoints(); ++j)
    {
      if (_histModel[i][j])
      {
        _cf[i][j] =  _histData[i][j];
        _cf[i][j] /= 1.0 * _histModel[i][j];
      }
    }
  }
  normalize(_cf, _pairsModel / _pairsData);
}

/*
bool
CorrelationTimeArcGrbcat::save(const std::string& filename)
{
  std::ofstream ofsCat(filename + "-cat.tsv");
  std::ofstream ofsBkg(filename + "-bkg.tsv");
  std::ofstream ofsFun(filename + "-fun.tsv");
  std::ofstream ofsPar(filename + "-par.tsv");

  if (ofsCat.fail() || ofsBkg.fail() || ofsFun.fail() || ofsPar.fail())
  {
    std::stringstream ss;
    ss << "Failed to save CF. Unable to create file=" << filename << "-*.tsv";
    Exception exc(type::EXCEPTION_CRITICAL, ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  ofsPar << "x_range\t"  << _xRange  << std::endl;
  ofsPar << "x_points\t" << _xPoints << std::endl;
  ofsPar << "y_range\t"  << _yRange  << std::endl;
  ofsPar << "y_points\t" << _yPoints << std::endl;
  ofsPar << "pairs_data\t" << _pairsData << std::endl;
  ofsPar << "pairs_model\t" << _pairsModel << std::endl;

  for (std::size_t i = 0; i < _yPoints; ++i)
  {
    bool first = true;
    for (std::size_t j = 0; j < _xPoints; ++j)
    {
      if (!first)
      {
        ofsCat << "\t";
        ofsBkg << "\t";
        ofsFun << "\t";
      }
      else
      {
        first = false;
      }
      ofsCat << _histData[i][j];
      ofsBkg << _histModel[i][j];
      ofsFun << _cf[i][j];
    }
    ofsCat << std::endl;
    ofsBkg << std::endl;
    ofsFun << std::endl;
  }

  ofsCat.close();
  ofsBkg.close();
  ofsFun.close();
  ofsPar.close();
  return true;
}
*/


bool
CorrelationTimeArcGrbcat::checkCatalog(Catalog& catalog)
{
  if (catalog.getType() != type::GRBCAT)
  {
    return false;
  }

  CatalogEntryGrbcat* entry = dynamic_cast<CatalogEntryGrbcat*>(*catalog.getEntries().begin());
  if (!entry)
  {
    return false;
  }

  return true;
}

void
CorrelationTimeArcGrbcat::filterEntries(Catalog& catalog,
                                        std::vector<CatalogEntry*>& entries)
{
  if (!checkCatalog(catalog))
  {
    // TODO Exception
    return;
  }

  for (CatalogEntry* entry : catalog.getEntries())
  {
    CatalogEntryGrbcat* entryGrbcat = static_cast<CatalogEntryGrbcat*>(entry);
    if (entryGrbcat->getCoordFlag() != -1 &&
        entryGrbcat->getCoodinates().getCoorType() == type::EQUATORIAL_J2000 &&
        entryGrbcat->getCoodinates().getDateType() == type::MODIFIED_JULIAN_DATE &&
        entryGrbcat->getCoodinates().getTimeMJD() != 0.0)
    {
      entries.push_back(entryGrbcat);
    }
  }
  TRACE("filterEntries size = " << entries.size());
}

void
CorrelationTimeArcGrbcat::initiate()
{
  TRACE("X: range = " << getXRange() << ", points = " << getXPoints() << ", delta = " << getXDelta());
  TRACE("Y: range = " << getYRange() << ", points = " << getYPoints() << ", delta = " << getYDelta());
  _histData.resize(getYPoints(), std::vector<std::size_t>(getXPoints(), 0));
  _histModel.resize(getYPoints(), std::vector<std::size_t>(getXPoints(), 0));
  _cf.resize(getYPoints(), std::vector<type::Float>(getXPoints(), 0.0));
}

std::size_t
CorrelationTimeArcGrbcat::generateCF(Catalog& catalog,
                                     std::vector< std::vector<std::size_t> > hist)
{
  std::size_t pairs = 0;
  GreatCircleDistance distance(_formula);
  std::vector<CatalogEntry*> entries;

  filterEntries(catalog, entries);

  const std::size_t points = entries.size();
  const std::size_t pairsAll = points * (points -1) / 2;
  const std::size_t mod = std::pow(10.0, std::floor(std::log10(pairsAll)) - 4);

  std::printf("ENTRIES = %ld, PAIRS = %ld\n", points, pairsAll);

  std::size_t k = 0;
  for (std::size_t i = 0; i < points - 1; ++i)
  {
    CatalogEntryGrbcat* iEntry = static_cast<CatalogEntryGrbcat*>(entries[i]);
    for (std::size_t j = i + 1; j < points; ++j)
    {
      CatalogEntryGrbcat* jEntry = static_cast<CatalogEntryGrbcat*>(entries[j]);
      type::Float time = std::fabs(jEntry->getCoodinates().getTimeMJD() -
                                   iEntry->getCoodinates().getTimeMJD());
      type::Float dist = distance(jEntry->getCoodinates(), iEntry->getCoodinates());

      std::size_t xIdx = std::floor(time * getXDelta());
      std::size_t yIdx = std::floor(dist * getYDelta());

      if (xIdx < getXPoints() && yIdx < getYPoints())
      {
        ++hist[yIdx][xIdx];
        ++pairs;
      }

      if (++k % mod == 0)
      {
        std::printf("\rProgress %3.2f%% %ld/%ld - pairs = %ld" ,
                    100.0 * k / pairsAll, k, pairsAll, pairs);
      }
    }
  }
  std::printf("\rProgress %3.2f%% %ld/%ld - pairs = %ld\n" ,
              100.0 * k / pairsAll, k, pairsAll, pairs);

  return pairs;
}

void
CorrelationTimeArcGrbcat::normalize(std::vector< std::vector<type::Float>>& cf, type::Float norm)
{
  for (std::size_t i = 0; i < getYPoints(); ++i)
  {
    for (std::size_t j = 0; j < getXPoints(); ++j)
    {
      cf[i][j] *= norm;
    }
  }
}

} // namespace grb
