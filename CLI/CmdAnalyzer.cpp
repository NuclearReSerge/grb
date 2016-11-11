#include "CLI/CmdAnalyzer.h"

#include "Analyzer/AnalyzerFactory.h"
#include "Analyzer/AnalyzerCmdMapper.h"
#include "Analyzer/AnalyzerMapper.h"
#include "Main/AnalysisData.h"

namespace
{

const char* HELP_SHORT = "performs correlation analysis.";
const char* HELP_LONG = "create <ANALYZER_NAME> | genetate | help [<ANALYZER_NAME>] | <SUB_COMMAND>\n"
"\n"
"    create <ANALYZER_NAME> : crate an analyzer,\n"
"    list                   : list configuration,\n"
"    help [<ANALYZER_NAME>] : help information on a current or specific analyzer,\n"
"    SUB_COMMAND            : analyzer specific command,\n"
"    ANALYZER_NAME          : analyzer name.\n"
"\n"
"Available analyzers:\n";

} // namespace

namespace grb
{

type::AnalyzerType
CmdAnalyzer::getMappedObjectVal(std::string& objStr)
{
  return AnalyzerMapper::instance()->getValue(objStr);
}

type::AnalyzerCmdType
CmdAnalyzer::getMappedSubCmdVal(std::string& cmdStr)
{
  return AnalyzerCmdMapper::instance()->getValue(cmdStr);
}

std::string
CmdAnalyzer::getMappedSubCmdStr(type::AnalyzerCmdType cmdVal)
{
  return AnalyzerCmdMapper::instance()->getKey(cmdVal);
}

bool
CmdAnalyzer::isObjectCreated()
{
  return AnalysisData::instance()->getAnalyzer() != nullptr;
}

std::string
CmdAnalyzer::getCreatedObjectName()
{
  if (!isObjectCreated())
    return "not-created";
  return AnalyzerMapper::instance()->getKey(AnalysisData::instance()->getAnalyzer()->getType());
}

bool
CmdAnalyzer::doParse(std::list<std::string>& tokens)
{
  switch (_subCmd)
  {
    case type::ANALYZER_LIST:
      return parseList(tokens);
    default:
      break;
  }

  if (isObjectCreated())
  {
    return AnalysisData::instance()->getAnalyzer()->parse(_subCmd, tokens);
  }
  return false;
}

void
CmdAnalyzer::doExecute()
{
  switch (_subCmd)
  {
    case type::ANALYZER_LIST:
    {
      executeList();
      return;
    }
    default:
      break;
  }

  if (isObjectCreated())
  {
    return AnalysisData::instance()->getAnalyzer()->execute(_subCmd);
  }
}

std::string
CmdAnalyzer::doHelp(type::CommandHelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  std::stringstream ss;
  ss << HELP_LONG;
  for(int i = 0; i < type::UNDEFINED_ANALYZER; ++i)
  {
    ss << "  "
       << AnalyzerMapper::instance()->getKey((type::AnalyzerType) i)
       << std::endl;
  }

  return ss.str();
}

void
CmdAnalyzer::executeCreate()
{
  Analyzer* object = AnalyzerFactory::instance()->createType(_type);
  if (!object)
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Analyzer '" << AnalyzerMapper::instance()->getKey(_type)
       << "' not created.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  AnalysisData::instance()->setAnalyzer(object);
}

void
CmdAnalyzer::executeHelp()
{
  std::stringstream ss;

  if (isObjectCreated())
  {
    ss << AnalysisData::instance()->getAnalyzer()->help();
  }
  else
  {
    Analyzer* object = AnalyzerFactory::instance()->createType(_type);
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
CmdAnalyzer::parseList(std::list<std::string>& tokens)
{
  tokens.clear();
  return true;
}

void
CmdAnalyzer::executeList()
{
}

} // namespace grb
