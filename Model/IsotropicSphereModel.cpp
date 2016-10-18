#include "Model/IsotropicSphereModel.h"

#include "Data/Catalog.h"
#include "Data/CatalogEntryFactory.h"
#include "Data/CatalogEntryGrbcat.h"
#include "Model/ModelCmdMapper.h"
#include "Model/ModelMapper.h"
#include "Tools/SyntaxVerifier.h"

namespace grb
{

IsotropicSphereModel::IsotropicSphereModel(type::ModelType type)
  : Model(type)
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
  if (tokens.empty())
    return false;

  switch (cmd)
  {
    case type::MODEL_SET_TIME:
    case type::MODEL_SET_PHI:
    case type::MODEL_SET_THETA:
    {
      SyntaxVerifier verifier(tokens);
      if (!verifier.verifyRange())
      {
        std::stringstream ss;
        ss << "Parsing failed. Model '" << ModelMapper::instance()->getKey(getType())
           << "'. Command '" << ModelCmdMapper::instance()->getKey(cmd)
           << "' requires range format.";
        Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                      ss.str(), PRETTY_FUNCTION);
        throw exc;
      }
      _minValue = std::strtod(verifier.getExtracted()[0]->c_str(), 0);
      _maxValue = std::strtod(verifier.getExtracted()[1]->c_str(), 0);
      tokens.clear();
      return true;
    }
    case type::MODEL_SET_CATALOG_TYPE:
    {
      try
      {
        _catType = CatalogEntryMapper::instance()->getValue(tokens.front());
      }
      catch (Exception&)
      {
        std::stringstream ss;
        ss << "Parsing failed. Model '" << ModelMapper::instance()->getKey(getType())
           << "'. Command '" << ModelCmdMapper::instance()->getKey(cmd)
           << "'. Invalid catalog type '" << tokens.front() << "'.";
        Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                      ss.str(), PRETTY_FUNCTION);
        throw exc;
      }

      tokens.pop_front();
      return true;
    }
    default:
      break;
  }
  return false;
}

void
IsotropicSphereModel::doExecute(type::ModelCmdType cmd)
{
  switch (cmd)
  {
    case type::MODEL_SET_TIME:
    {
      setTimeRange(_minValue, _maxValue);
      break;
    }
    case type::MODEL_SET_PHI:
    {
      setPhiRange(_minValue, _maxValue);
      break;
    }
    case type::MODEL_SET_THETA:
    {
      setThetaRange(_minValue, _maxValue);
      break;
    }
    case type::MODEL_SET_CATALOG_TYPE:
      break;
    default:
      break;
  }
}

void
IsotropicSphereModel::doGenerate(Catalog& catalog)
{
  if (catalog.getType() != _catType)
  {
    std::stringstream ss;
    ss << "Generate failed. Model '" << ModelMapper::instance()->getKey(getType())
       << "'. Provided catalog type doesn't match requested one.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  for (std::size_t i = 0; i < getNumberOfEntries(); ++i)
  {
    CatalogEntryGrbcat* entry = createEntry();
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

CatalogEntryGrbcat*
IsotropicSphereModel::createEntry()
{
  CatalogEntry* entryBase = CatalogEntryFactory::instance()->createType(_catType);
  if (!entryBase)
  {
    std::stringstream ss;
    ss << "Generate failed. Model '" << ModelMapper::instance()->getKey(getType())
       << "'. Unable to create catalog entry.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  CatalogEntryGrbcat* entry = dynamic_cast<CatalogEntryGrbcat*>(entryBase);
  if (!entry)
  {
    std::stringstream ss;
    ss << "Generate failed. Model '" << ModelMapper::instance()->getKey(getType())
       << "'. Created wrong type of catalog.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  return entry;
}

} // namespace grb
