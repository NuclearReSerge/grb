#include "CLI/CmdModel.h"

#include "CLI/CommandMapper.h"
#include "Main/AnalysisData.h"
#include "Model/ModelCmdMapper.h"
#include "Model/ModelFactory.h"

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

void
errorHeader(std::stringstream& ss, type::ModelCmdType subCmd = type::UNDEFINED_MODEL_CMD)
{
  ss << "Command " << CommandMapper::instance()->getKey(type::CMD_MODEL) << " ";
  if (subCmd != type::UNDEFINED_MODEL_CMD)
    ss << ModelCmdMapper::instance()->getKey(subCmd) << " ";
  ss << "failed. ";
}

CmdModel::CmdModel()
  : Cmd(type::CMD_MODEL), _subCmd(type::UNDEFINED_MODEL_CMD),
    _modelType(type::UNDEFINED_MODEL)
{
}

bool
CmdModel::doParse(std::list<std::string>& tokens)
{
  if (tokens.empty())
  {
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  help(type::HELP_LONG), PRETTY_FUNCTION);
    throw exc;
  }

  try
  {
    _subCmd = ModelCmdMapper::instance()->getValue(tokens.front());
    tokens.pop_front();
  }
  catch(Exception& )
  {
    std::stringstream ss;
    errorHeader(ss);
    ss << "Received unknown subcommand " << tokens.front();
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
  }

  switch (_subCmd)
  {
    case type::MODEL_CREATE:
    {
      return parseCreate(tokens);
    }
    case type::MODEL_GENERATE:
    {
      return parseGenerate(tokens);
    }
    case type::MODEL_HELP:
    {
      return parseHelp(tokens);
    }
    default:
      break;
  }

  if (G_Model().get())
  {
    return G_Model().get()->parse(_subCmd, tokens);
  }
  return false;
}

void
CmdModel::doExecute()
{
  switch (_subCmd)
  {
    case type::MODEL_CREATE:
    {
      executeCreate();
      break;
    }
    case type::MODEL_GENERATE:
    {
      executeGenerate();
      break;
    }
    case type::MODEL_HELP:
    {
      executeHelp();
      break;
    }
    default:
      break;
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

bool
CmdModel::parseCreate(std::list<std::string>& tokens)
{
  if (G_Model().get())
  {
    std::stringstream ss;
    errorHeader(ss, type::MODEL_CREATE);
    ss << "Previous model "
       << ModelMapper::instance()->getKey(G_Model().get()->getType())
       << " already exists.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  if (tokens.empty())
  {
    std::stringstream ss;
    errorHeader(ss, type::MODEL_CREATE);
    ss << "Arguments required.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  try
  {
    _modelType = ModelMapper::instance()->getValue(tokens.front());
    tokens.pop_front();
  }
  catch (Exception& )
  {
    std::stringstream ss;
    errorHeader(ss, type::MODEL_CREATE);
    ss << "Unknown model " << tokens.front();
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
  }

  return true;
}

bool
CmdModel::parseGenerate(std::list<std::string>& tokens)
{
  tokens.clear();
  return true;
}

bool
CmdModel::parseHelp(std::list<std::string>& tokens)
{
  if (tokens.empty())
  {
    if (G_Model().get())
      return true;

    std::stringstream ss;
    errorHeader(ss, type::MODEL_HELP);
    ss << "Arguments required.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  try
  {
    _modelType = ModelMapper::instance()->getValue(tokens.front());
    tokens.clear();
  }
  catch (Exception& )
  {
    std::stringstream ss;
    errorHeader(ss, type::MODEL_HELP);
    ss << "Unknown model " << tokens.front();
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
  }
  return true;
}

void
CmdModel::executeCreate()
{
  Model* model = ModelFactory::instance()->createType(_modelType);
  if (!model)
  {
    std::stringstream ss;
    errorHeader(ss, type::MODEL_CREATE);
    ss << "Model " << ModelMapper::instance()->getKey(_modelType) << " not created.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  G_Model().reset(model);
}

void
CmdModel::executeGenerate()
{
  if (!G_Model().get())
  {
    std::stringstream ss;
    errorHeader(ss, _subCmd);
    ss << "Create a model first.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }


  if (!G_Model().get()->isConfigured())
  {
    std::stringstream ss;
    errorHeader(ss, type::MODEL_GENERATE);
    ss << "Model is not configured.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  if (!G_CatalogData().get())
  {
    std::stringstream ss;
    errorHeader(ss, type::MODEL_GENERATE);
    ss << "Noting to model. Provide a databse first.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  Catalog* catalog = new Catalog(G_CatalogData().get()->getType());
  G_Model().get()->generate(*catalog);
  G_CatalogModel().reset(catalog);
}

void
CmdModel::executeHelp()
{
  std::stringstream ss;
  Model* model = nullptr;

  if (G_Model().get())
  {
    model = G_Model().get();
    ss << model->help();
  }
  else
  {
    model = ModelFactory::instance()->createType(_modelType);
    if (model)
    {
      ss << model->help();
      delete model;
    }
  }
  Exception exc((type::ExceptionLevel) (type::EXCEPTION_LOW + type::EXCEPTION_MOD_NO_PREFIX),
                ss.str(), PRETTY_FUNCTION);
  throw exc;
}

} // namespace grb
