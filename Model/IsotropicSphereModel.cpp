#include "Model/IsotropicSphereModel.h"

#include "Data/Catalog.h"
#include "Data/CatalogEntryFactory.h"
#include "Data/CatalogEntryGrbcat.h"

namespace grb
{

IsotropicSphereModel::IsotropicSphereModel()
  : Model(type::ISOTROPIC_SPHERE)
{
  setTimeRange(0.0, 1.0);
  setPhiRange(0.0, 2.0 * M_PIl);
  setThetaRange(-M_PI_2l, M_PI_2l);
}

IsotropicSphereModel::~IsotropicSphereModel()
{
}

bool
IsotropicSphereModel::doParse(type::ModelCmdType cmd, std::list<std::string>& tokens)
{
  switch (cmd)
  {
    case type::MODEL_SET_TIME:
    {
      break;
    }
    case type::MODEL_SET_PHI:
    {
      break;
    }
    case type::MODEL_SET_THETA:
    {
      break;
    }
    default:
      break;
  }

  tokens.empty();
  return true;
}

void
IsotropicSphereModel::doGenerate(Catalog& catalog)
{
  CatalogEntry* entryBase;
  for (std::size_t i = 0; i < getNumberOfEntries(); ++i)
  {
    entryBase = CatalogEntryFactory::instance()->createType(type::GRBCAT_ENTRY);
    CatalogEntryGrbcat* entry = static_cast<CatalogEntryGrbcat*>(entryBase);

    entry->getCoordFlag() = 0.0;
    entry->getCoodinates().getX0() = _time(getGenerator());
    entry->getCoodinates().getX1() = 1.0;
    entry->getCoodinates().getX2() = _phi(getGenerator());
    entry->getCoodinates().getX3() = _theta(getGenerator());
    catalog.getEntries().push_back(entry);
  }
}

std::string
IsotropicSphereModel::doHelp()
{
  return "IsotropicSphereModel help";
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
