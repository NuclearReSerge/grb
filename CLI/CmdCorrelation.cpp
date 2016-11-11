#include "CLI/CmdCorrelation.h"

#include "Correlation/CorrelationCmdMapper.h"
#include "Correlation/CorrelationMapper.h"
#include "Correlation/CorrelationFactory.h"
#include "Main/AnalysisData.h"

namespace
{

const char* HELP_SHORT = "generates correlation function.";
const char* HELP_LONG = "create <CORRELATION_NAME> | genetate | save | help [<MODEL_NAME>] | <SUB_COMMAND>\n"
"\n"
"    create <CORRELATION_NAME> : crate a correlation,\n"
"    generate                  : generate correlation function,\n"
"    save                      : save correlation function to file,\n"
"    help [<CORRELATION_NAME>] : help information on a current or specific correlation,\n"
"    SUB_COMMAND               : correlation specific command,\n"
"    CORRELATION_NAME          : correlation name.\n"
"\n"
"Available correlations:\n";

} // namespace

namespace grb
{

type::CorrelationType
CmdCorrelation::getMappedObjectVal(std::string& objStr)
{
  return CorrelationMapper::instance()->getValue(objStr);
}

type::CorrelationCmdType
CmdCorrelation::getMappedSubCmdVal(std::string& cmdStr)
{
  return CorrelationCmdMapper::instance()->getValue(cmdStr);
}

std::string
CmdCorrelation::getMappedSubCmdStr(type::CorrelationCmdType cmdVal)
{
  return CorrelationCmdMapper::instance()->getKey(cmdVal);
}

bool
CmdCorrelation::isObjectCreated()
{
  return AnalysisData::instance()->getCorrelation() != nullptr;
}

std::string
CmdCorrelation::getCreatedObjectName()
{
  if (!isObjectCreated())
    return "not-created";
  return CorrelationMapper::instance()->getKey(AnalysisData::instance()->getCorrelation()->getType());
}

bool
CmdCorrelation::doParse(std::list<std::string>& tokens)
{
  switch (_subCmd)
  {
    case type::CORRELATION_GENERATE:
      return parseGenerate(tokens);
    default:
      break;
  }

  if (isObjectCreated())
  {
    return AnalysisData::instance()->getCorrelation()->parse(_subCmd, tokens);
  }
  return false;
}

void
CmdCorrelation::doExecute()
{
  switch (_subCmd)
  {
    case type::CORRELATION_GENERATE:
    {
      executeGenerate();
      return;
    }
    default:
      break;
  }

  if (isObjectCreated())
  {
    return AnalysisData::instance()->getCorrelation()->execute(_subCmd);
  }
}

std::string
CmdCorrelation::doHelp(type::CommandHelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  std::stringstream ss;
  ss << HELP_LONG;
  for(int i = 0; i < type::UNDEFINED_CORRELATION; ++i)
  {
    ss << "  "
       << CorrelationMapper::instance()->getKey((type::CorrelationType) i)
       << std::endl;
  }

  return ss.str();
}

void
CmdCorrelation::executeCreate()
{
  Correlation* object = CorrelationFactory::instance()->createType(_type);
  if (!object)
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Correlation '" << CorrelationMapper::instance()->getKey(_type)
       << "' not created.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  AnalysisData::instance()->setCorrelation(object);
}

void
CmdCorrelation::executeHelp()
{
  std::stringstream ss;

  if (isObjectCreated())
  {
    ss << AnalysisData::instance()->getCorrelation()->help();
  }
  else
  {
    Correlation* object = CorrelationFactory::instance()->createType(_type);
    if (object)
    {
      ss << object->help();
      delete object;
    }
    else
    {
      return;
    }
  }
  Exception exc(type::EXCEPTION_LOW + type::EXCEPTION_MOD_NO_PREFIX,
                ss.str(), PRETTY_FUNCTION);
  throw exc;
}

bool
CmdCorrelation::parseGenerate(std::list<std::string>& tokens)
{
  tokens.clear();
  return true;
}

void
CmdCorrelation::executeGenerate()
{
  if (!AnalysisData::instance()->getCorrelation())
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Create a correlation first.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  if (!AnalysisData::instance()->getCorrelation()->isConfigured())
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Correlation is not configured.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  if (!AnalysisData::instance()->getCatalogData())
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Unable to generate correlation. Provide a databse first.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  if (!AnalysisData::instance()->getCatalogModel())
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Unable to generate correlation. Provide a model first.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  AnalysisData::instance()->getCorrelation()->generate(
        *AnalysisData::instance()->getCatalogData(),
        *AnalysisData::instance()->getCatalogModel());
}

} // namespace grb
