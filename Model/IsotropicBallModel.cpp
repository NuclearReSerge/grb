#include "Model/IsotropicBallModel.h"

#include "Data/Catalog.h"
#include "Data/CatalogEntryGrbcat.h"

namespace grb
{

IsotropicBallModel::IsotropicBallModel()
  : ModelBase(type::ISOTROPIC_BALL)
{
  setTimeRange(0.0, 1.0);
  setRadiusRange(0.0, 2.0 * M_PIl);
  setPhiRange(0.0, 2.0 * M_PIl);
  setThetaRange(-M_PI_2l, M_PI_2l);
}

IsotropicBallModel::~IsotropicBallModel()
{
}

bool
IsotropicBallModel::parse(std::list<std::string>& subcmd)
{
  return subcmd.empty();
}

void
IsotropicBallModel::generate(Catalog& catalog, std::size_t entries)
{
  for (std::size_t i = 0; i < entries; ++i)
  {
    CatalogEntryGRBCAT* entry = static_cast<CatalogEntryGRBCAT*>(catalog.createEntry());
    entry->getCoordFlag() = 0.0;
    entry->getTime().getX0() = _time(getGenerator());
    entry->getCoodinates().getX1() = _r(getGenerator());
    entry->getCoodinates().getX2() = _phi(getGenerator());
    entry->getCoodinates().getX3() = _theta(getGenerator());
    catalog.addEntry(entry);
  }
}

void
IsotropicBallModel::setTimeRange(double min, double max)
{
  std::uniform_real_distribution<>::param_type par(min, max);
  _time.param(par);
}

void
IsotropicBallModel::setRadiusRange(double min, double max)
{
  std::uniform_real_distribution<>::param_type par(min, max);
  _r.param(par);
}

void
IsotropicBallModel::setPhiRange(double min, double max)
{
  std::uniform_real_distribution<>::param_type par(min, max);
  _phi.param(par);
}

void
IsotropicBallModel::setThetaRange(double min, double max)
{
  std::uniform_real_distribution<>::param_type par(min, max);
  _theta.param(par);
}

}