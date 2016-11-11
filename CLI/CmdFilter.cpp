#include "CLI/CmdFilter.h"

#include "Filter/FilterFactory.h"
#include "Filter/FilterCmdMapper.h"
#include "Filter/FilterMapper.h"
#include "Main/AnalysisData.h"

namespace
{

const char* HELP_SHORT = "filters catalog entries.";
const char* HELP_LONG = "<SUB_COMMAND>";

} // namespace

namespace grb
{


type::FilterType
CmdFilter::getMappedObjectVal(std::string& objStr)
{
  return FilterMapper::instance()->getValue(objStr);
}

type::FilterCmdType
CmdFilter::getMappedSubCmdVal(std::string& cmdStr)
{
  return FilterCmdMapper::instance()->getValue(cmdStr);
}

std::string
CmdFilter::getMappedSubCmdStr(type::FilterCmdType cmdVal)
{
  return FilterCmdMapper::instance()->getKey(cmdVal);
}

bool
CmdFilter::isObjectCreated()
{
  return AnalysisData::instance()->getFilter() != nullptr;
}

std::string
CmdFilter::getCreatedObjectName()
{
  if (!isObjectCreated())
    return "not-created";
  return FilterMapper::instance()->getKey(AnalysisData::instance()->getFilter()->getType());
}

bool
CmdFilter::doParse(std::list<std::string>& tokens)
{
  switch (_subCmd)
  {
    default:
      break;
  }

  if (isObjectCreated())
  {
    return AnalysisData::instance()->getFilter()->parse(_subCmd, tokens);
  }
  return false;
}

void
CmdFilter::doExecute()
{
  switch (_subCmd)
  {
    default:
      break;
  }

  if (isObjectCreated())
  {
    return AnalysisData::instance()->getFilter()->execute(_subCmd);
  }
}

std::string
CmdFilter::doHelp(type::CommandHelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  std::stringstream ss;
  ss << HELP_LONG;
  for(int i = 0; i < type::UNDEFINED_FILTER; ++i)
  {
    ss << "  "
       << FilterMapper::instance()->getKey((type::FilterType) i)
       << std::endl;
  }

  return ss.str();
}

void
CmdFilter::executeCreate()
{
  Filter* object = FilterFactory::instance()->createType(_type);
  if (!object)
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Filter '" << FilterMapper::instance()->getKey(_type)
       << "' not created.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  AnalysisData::instance()->setFilter(object);
}

void
CmdFilter::executeHelp()
{
  std::stringstream ss;

  if (isObjectCreated())
  {
    ss << AnalysisData::instance()->getFilter()->help();
  }
  else
  {
    Filter* object = FilterFactory::instance()->createType(_type);
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

} // namespace grb
