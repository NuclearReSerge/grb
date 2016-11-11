#include "CLI/CmdModel.h"

#include "Catalog/Catalog.h"
#include "CLI/CommandMapper.h"
#include "Main/AnalysisData.h"
#include "Model/ModelCmdMapper.h"
#include "Model/ModelFactory.h"
#include "Model/ModelMapper.h"

#include <sstream>

namespace
{

const char* HELP_SHORT = "theoretical model.";
const char* HELP_LONG = "[create <MODEL_NAME>] | [genetate] | [help [<MODEL_NAME>]] | [<SUB_COMMAND>]\n"
"\n"
"    create <MODEL_NAME> : crate a theoretical model,\n"
"    generate            : generate data,\n"
"    help [<MODEL_NAME>] : help information on a current or specific model,\n"
"    SUB_COMMAND         : model specific command,\n"
"    MODEL_NAME          : model name.\n"
"\n"
"Available models:\n";

} // namespace

namespace grb
{

type::ModelType
CmdModel::getMappedObjectVal(std::string& objStr)
{
  return ModelMapper::instance()->getValue(objStr);
}

type::ModelCmdType
CmdModel::getMappedSubCmdVal(std::string& cmdStr)
{
  return ModelCmdMapper::instance()->getValue(cmdStr);
}

std::string
CmdModel::getMappedSubCmdStr(type::ModelCmdType cmdVal)
{
  return ModelCmdMapper::instance()->getKey(cmdVal);
}

bool
CmdModel::isObjectCreated()
{
  return AnalysisData::instance()->getModel() != nullptr;
}

std::string
CmdModel::getCreatedObjectName()
{
  if (!isObjectCreated())
    return "not-created";
  return ModelMapper::instance()->getKey(AnalysisData::instance()->getModel()->getType());
}


bool
CmdModel::doParse(std::list<std::string>& tokens)
{
  switch (_subCmd)
  {
    case type::MODEL_GENERATE:
      return parseGenerate(tokens);
    default:
      break;
  }

  if (isObjectCreated())
  {
    return AnalysisData::instance()->getModel()->parse(_subCmd, tokens);
  }
  return false;
}

void
CmdModel::doExecute()
{
  switch (_subCmd)
  {
    case type::MODEL_GENERATE:
    {
      executeGenerate();
      return;
    }
    default:
      break;
  }

  if (isObjectCreated())
  {
    return AnalysisData::instance()->getModel()->execute(_subCmd);
  }
}

std::string
CmdModel::doHelp(type::CommandHelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  std::stringstream ss;
  ss << HELP_LONG;
  for(int i = 0; i < type::UNDEFINED_MODEL; ++i)
  {
    ss << "  "
       << ModelMapper::instance()->getKey((type::ModelType) i)
       << std::endl;
  }

  return ss.str();
}

void
CmdModel::executeCreate()
{
  Model* object = ModelFactory::instance()->createType(_type);
  if (!object)
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Model " << ModelMapper::instance()->getKey(_type) << " not created.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  AnalysisData::instance()->setModel(object);
}

void
CmdModel::executeHelp()
{
  std::stringstream ss;

  if (AnalysisData::instance()->getModel())
  {
    ss << AnalysisData::instance()->getModel()->help();
  }
  else
  {
    Model* object = ModelFactory::instance()->createType(_type);
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
CmdModel::parseGenerate(std::list<std::string>& tokens)
{
  tokens.clear();
  return true;
}

void
CmdModel::executeGenerate()
{
  if (!AnalysisData::instance()->getModel())
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Create a model first.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  if (!AnalysisData::instance()->getModel()->isConfigured())
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Model is not configured.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  if (!AnalysisData::instance()->getCatalogData())
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Noting to model. Provide a databse first.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  Catalog* catalog = new Catalog(AnalysisData::instance()->getCatalogData()->getType());
  AnalysisData::instance()->getModel()->generate(*catalog);
  AnalysisData::instance()->setCatalogModel(catalog);
}

} // namespace grb
