#include "Model/IsotropicSphereModel.h"

#include "Data/Catalog.h"
#include "Data/CatalogEntryGrbcat.h"

namespace grb
{

IsotropicSphereModel::IsotropicSphereModel()
  : ModelBase(type::ISOTROPIC_SPHERE)
{
  setTimeRange(0.0, 1.0);
  setPhiRange(0.0, 2.0 * M_PIl);
  setThetaRange(-M_PI_2l, M_PI_2l);
}

IsotropicSphereModel::~IsotropicSphereModel()
{
}

bool
IsotropicSphereModel::parse(std::list<std::string>& subcmd)
{
  return subcmd.empty();
}

void
IsotropicSphereModel::generate(Catalog& catalog, std::size_t entries)
{
  for (std::size_t i = 0; i < entries; ++i)
  {
    CatalogEntryGRBCAT* entry = static_cast<CatalogEntryGRBCAT*>(catalog.createEntry());
    entry->getCoordFlag() = 0.0;
    entry->getTime().getX0() = _time(getGenerator());
    entry->getCoodinates().getX1() = 1.0;
    entry->getCoodinates().getX2() = _phi(getGenerator());
    entry->getCoodinates().getX3() = _theta(getGenerator());
    catalog.addEntry(entry);
  }
}

void
IsotropicSphereModel::setTimeRange(double min, double max)
{
  std::uniform_real_distribution<>::param_type par(min, max);
  _time.param(par);
}

void
IsotropicSphereModel::setPhiRange(double min, double max)
{
  std::uniform_real_distribution<>::param_type par(min, max);
  _phi.param(par);
}

void
IsotropicSphereModel::setThetaRange(double min, double max)
{
  std::uniform_real_distribution<>::param_type par(min, max);
  _theta.param(par);
}

}