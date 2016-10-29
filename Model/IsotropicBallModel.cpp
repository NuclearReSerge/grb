#include "Model/IsotropicBallModel.h"

#include "Data/CatalogEntryMapper.h"
#include "Model/ModelCmdMapper.h"
#include "Model/ModelMapper.h"
#include "Tools/SyntaxVerifier.h"

namespace
{

const char* HELP = "\n"
"<SUB_COMMAND> = set-catalog-type <CATALOG_TYPE> | set-time <RANGE> | set-radius <RANGE> | set-phi <RANGE> | set-theta <RANGE>\n"
"\n"
"    set-catalog-type    : set the type of catalog entries that will be generated,\n"
"    set-time            : set time range,\n"
"    set-radius          : set radius range,\n"
"    set-phi             : set phi range (right ascension),\n"
"    set-theta           : set theta range (declination).\n"
"\n"
"    RANGE format : ( min , max ) - whitespace are ignored\n"
"         Example : (-2.0,10.135)\n"
"\n"
"Available CATALOG_TYPE :\n";

} // namespace

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
  std::stringstream ss;
  ss << HELP;
  for(int i = 0; i < type::UNDEFINED_CATALOG; ++i)
  {
    ss << "  "
       << CatalogEntryMapper::instance()->getKey((type::CatalogType) i)
       << std::endl;
  }
  return ss.str();
}

void
IsotropicBallModel::setRadiusRange(double min, double max)
{
  std::uniform_real_distribution<>::param_type par(min, max);
  _r.param(par);
}

} // namespace grb
