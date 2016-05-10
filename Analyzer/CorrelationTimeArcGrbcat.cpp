#include "Analyzer/CorrelationTimeArcGrbcat.h"
#include "Common/Exception.h"
#include "Common/Global.h"
#include "Data/Catalog.h"
#include "Data/CatalogEntryGrbcat.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <random>
#include <sstream>

#include "Common/trace.h"

namespace grb
{


CorrelationTimeArcGrbcat::CoordinatesBkg::CoordinatesBkg(type::Float time,
                                                         type::Float hori,
                                                         type::Float vert)
  : Coordinates(type::J2000)
{
  _time = time;
  getHorizontal() = hori;
  getVertical() = vert;
}

const type::Float&
CorrelationTimeArcGrbcat::CoordinatesBkg::getTime() const
{
  return _time;
}

CorrelationTimeArcGrbcat::CorrelationTimeArcGrbcat()
  : Correlation(type::TIME_DIFF_VS_CIRCLE_DIST_GRBCAT), _formula(type::VINCENTY_FORMULAE),
    _pairsCfCat(0), _pairsCfBkg(0)
{
}

CorrelationTimeArcGrbcat::~CorrelationTimeArcGrbcat()
{
  for (std::vector<type::Float>& vecValue : _cf)
  {
    vecValue.clear();
  }
  _cf.clear();

  for (std::vector<std::size_t>& vecValue : _cfCat)
  {
    vecValue.clear();
  }
  _cfCat.clear();

  for (std::vector<std::size_t>& vecValue : _cfBkg)
  {
    vecValue.clear();
  }
  _cfBkg.clear();

}

bool
CorrelationTimeArcGrbcat::buildCF(const Catalog& catalog)
{
  initiate();

  TRACE("GENERATING CF CATALOG");
  _pairsCfCat = generateCFCAT(catalog);
  TRACE("GENERATING CF BACKGROUND");
  _pairsCfBkg = generateCFBKG(60000);

  TRACE("PAIRS: CF = " << _pairsCfCat << ", CFBKG = " << _pairsCfBkg);

  for (std::size_t i = 0; i < _yPoints; ++i)
  {
    for (std::size_t j = 0; j < _xPoints; ++j)
    {
      if (_cfBkg[i][j])
      {
        _cf[i][j] =  _cfCat[i][j];
        _cf[i][j] /= 1.0 * _cfBkg[i][j];
      }
    }
  }
  normalize(_cf, _pairsCfBkg / _pairsCfCat);

  return true;
}

bool
CorrelationTimeArcGrbcat::saveCF(const std::string& filename)
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
  ofsPar << "pairs_cat\t" << _pairsCfCat << std::endl;
  ofsPar << "pairs_bkg\t" << _pairsCfBkg << std::endl;

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
      ofsCat << _cfCat[i][j];
      ofsBkg << _cfBkg[i][j];
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
CorrelationTimeArcGrbcat::filterEntries(const Catalog& catalog,
                                        std::vector<const CatalogEntry*>& entries)
{
  if (!checkCatalog(catalog))
  {
    // TODO Exception
    return;
  }

  for (const CatalogEntry* entry : catalog)
  {
    const CatalogEntryGRBCAT* entryGrbcat = static_cast<const CatalogEntryGRBCAT*>(entry);
    if (entryGrbcat->getCoodinates().getType() == type::J2000 &&
        entryGrbcat->getCoodinates().getCoordFlag() != -1 &&
        entryGrbcat->getTime().getType() == type::MODIFIED_JULIAN_DATE &&
        entryGrbcat->getTime().getTimeMJD() != 0.0)
    {
      entries.push_back(entryGrbcat);
    }
  }
  TRACE("filterEntries size = " << entries.size());
}

void
CorrelationTimeArcGrbcat::initiate()
{
  TRACE("X: range = " << _xRange << ", points = " << _xPoints << ", delta = " << _xDelta);
  TRACE("Y: range = " << _yRange << ", points = " << _yPoints << ", delta = " << _yDelta);
  _cfCat.resize(_yPoints, std::vector<std::size_t>(_xPoints, 0));
  _cfBkg.resize(_yPoints, std::vector<std::size_t>(_xPoints, 0));
  _cf.resize(_yPoints, std::vector<type::Float>(_xPoints, 0.0));
}

std::size_t CorrelationTimeArcGrbcat::generateCFCAT(const Catalog& catalog)
{
  std::size_t pairs = 0;
  GreatCircleDistance distance(_formula);
  std::vector<const CatalogEntry*> entries;

  filterEntries(catalog, entries);

  const std::size_t points = entries.size();
  const std::size_t pairsAll = points * (points -1) / 2;
  const std::size_t mod = std::pow(10.0, std::floor(std::log10(pairsAll)) - 4);

  std::printf("ENTRIES = %ld, PAIRS = %ld\n", points, pairsAll);

  std::size_t k = 0;
  for (std::size_t i = 0; i < points - 1; ++i)
  {
    const CatalogEntryGRBCAT* iEntry = static_cast<const CatalogEntryGRBCAT*>(entries[i]);
    for (std::size_t j = i + 1; j < points; ++j)
    {
      const CatalogEntryGRBCAT* jEntry = static_cast<const CatalogEntryGRBCAT*>(entries[j]);
      type::Float time = std::fabs(jEntry->getTime().getTimeMJD() - iEntry->getTime().getTimeMJD());
      type::Float dist = distance(jEntry->getCoodinates(), iEntry->getCoodinates());

      std::size_t xIdx = std::floor(time * _xDelta);
      std::size_t yIdx = std::floor(dist * _yDelta);

      if (xIdx < _xPoints && yIdx < _yPoints)
      {
        ++_cfCat[yIdx][xIdx];
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
CorrelationTimeArcGrbcat::generateBackground(std::vector<CoordinatesBkg>& coorVec,
                                            std::size_t points)
{
  std::random_device hwGen;
  std::seed_seq seed{hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen()};
  std::mt19937_64 gen(seed);
  std::uniform_real_distribution<type::Float> distT(0.0, _xRange);
  std::uniform_real_distribution<type::Float> distH(0.0, 2.0 * M_PIl);
  std::uniform_real_distribution<type::Float> distV(-M_PI_2l, M_PI_2l);

  for (std::size_t i = 0; i < points - 1; ++i)
  {
    CoordinatesBkg item(distT(gen), distH(gen), distV(gen));
    coorVec.push_back(item);
  }
}

std::size_t
CorrelationTimeArcGrbcat::generateCFBKG(const std::size_t points)
{
  std::size_t pairs = 0;
  GreatCircleDistance distance(_formula);
  std::vector<CoordinatesBkg> entries;

  generateBackground(entries, points);

  const std::size_t pairsAll = points * (points -1) / 2;
  const std::size_t mod = std::pow(10.0, std::floor(std::log10(pairsAll)) - 4);

  std::printf("ENTRIES = %ld, PAIRS = %ld\n", points, pairsAll);

  std::size_t k = 0;
  for (std::size_t i = 0; i < points - 1; ++i)
  {
    CoordinatesBkg& iCoor = entries[i];
    for (std::size_t j = i + 1; j < points; ++j)
    {
      CoordinatesBkg& jCoor = entries[j];
      type::Float time = std::fabs(jCoor.getTime() - iCoor.getTime());
      type::Float dist = distance(jCoor, iCoor);

      std::size_t xIdx = std::floor(time * _xDelta);
      std::size_t yIdx = std::floor(dist * _yDelta);

      if (xIdx < _xPoints && yIdx < _yPoints)
      {
        ++_cfBkg[yIdx][xIdx];
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
  for (std::size_t i = 0; i < _yPoints; ++i)
  {
    for (std::size_t j = 0; j < _xPoints; ++j)
    {
      cf[i][j] *= norm;
    }
  }
}

}
