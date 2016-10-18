#include "Model/IsotropicBallModel.h"

#include "Model/ModelCmdMapper.h"
#include "Model/ModelMapper.h"
#include "Tools/SyntaxVerifier.h"


namespace grb
{

IsotropicBallModel::IsotropicBallModel(type::ModelType type)
  : IsotropicSphereModel(type)
{
  setRadiusRange(0.0, 1.0);
}

IsotropicBallModel::~IsotropicBallModel()
{
}

bool
IsotropicBallModel::doParse(type::ModelCmdType cmd, std::list<std::string>& tokens)
{
  if (tokens.empty())
    return false;

  switch (cmd)
  {
    case type::MODEL_SET_TIME:
    case type::MODEL_SET_PHI:
    case type::MODEL_SET_THETA:
    case type::MODEL_SET_CATALOG_TYPE:
    {
      return IsotropicSphereModel::doParse(cmd, tokens);
    }
    case type::MODEL_SET_RADIUS:
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
    default:
      break;
  }
  return false;
}

void
IsotropicBallModel::doExecute(type::ModelCmdType cmd)
{
  switch (cmd)
  {
    case type::MODEL_SET_TIME:
    case type::MODEL_SET_PHI:
    case type::MODEL_SET_THETA:
    case type::MODEL_SET_CATALOG_TYPE:
    {
      IsotropicSphereModel::doExecute(cmd);
      break;
    }
    case type::MODEL_SET_RADIUS:
    {
      setRadiusRange(_minValue, _maxValue);
      break;
    }
    default:
      break;
  }
}

std::string
IsotropicBallModel::doHelp()
{
  return "IsotropicBallModel help";
}

void
IsotropicBallModel::setRadiusRange(double min, double max)
{
  std::uniform_real_distribution<>::param_type par(min, max);
  _r.param(par);
}

} // namespace grb
