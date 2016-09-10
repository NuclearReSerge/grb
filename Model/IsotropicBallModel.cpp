#include "Model/IsotropicBallModel.h"

#include "Data/Catalog.h"
#include "Data/CatalogEntryFactory.h"
#include "Data/CatalogEntryGrbcat.h"


namespace grb
{

IsotropicBallModel::IsotropicBallModel()
  : Model(type::ISOTROPIC_BALL)
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
IsotropicBallModel::doParse(type::ModelCmdType cmd, std::list<std::string>& tokens)
{
  switch (cmd)
  {
    case type::MODEL_SET_TIME:
    {
      break;
    }
    case type::MODEL_SET_RADIUS:
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
IsotropicBallModel::doGenerate(Catalog& catalog)
{
  CatalogEntry* entryBase;
  for (std::size_t i = 0; i < getNumberOfEntries(); ++i)
  {
    entryBase = CatalogEntryFactory::instance()->createType(type::GRBCAT_ENTRY);
    CatalogEntryGrbcat* entry = static_cast<CatalogEntryGrbcat*>(entryBase);

    entry->getCoordFlag() = 0.0;
    entry->getCoodinates().getX0() = _time(getGenerator());
    entry->getCoodinates().getX1() = _r(getGenerator());
    entry->getCoodinates().getX2() = _phi(getGenerator());
    entry->getCoodinates().getX3() = _theta(getGenerator());
    catalog.getEntries().push_back(entry);
  }
}

std::string
IsotropicBallModel::doHelp()
{
  return "IsotropicBallModel help";
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
