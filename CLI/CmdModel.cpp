#include "CLI/CmdModel.h"

#include "CLI/CmdMapper.h"
#include "Main/AnalysisData.h"
#include "Model/ModelFactory.h"

#include <sstream>

namespace grb
{

namespace
{

const char* HELP_SHORT = "theoretical model.";
const char* HELP_LONG = "<SUB_COMMAND>";

}

CmdModel::CmdModel(CommandLine& cli)
  : Cmd(cli, type::CMD_MODEL)
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

  if (!G_Model().get())
  {
    modelNameMapping(tokens.front());
    tokens.pop_front();
  }
  G_Model().get()->parse(tokens);
  return true;
}

void
CmdModel::doExecute()
{
  if (!G_Model().get()->isConfigured())
    return;

  if (!G_CatalogData().get())
  {
    std::stringstream ss;
    ss << "Noting to model. Provide a databse first.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  Catalog* catalog = new Catalog(G_CatalogData().get()->getType());
  G_Model().get()->generate(*catalog);
  G_CatalogModel().reset(catalog);
}

std::string
CmdModel::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
}

void
CmdModel::modelNameMapping(const std::string& name)
{
  Model* model = ModelFactory::instance()->create(name);
  if (!model)
  {
    std::stringstream ss;
    ss << "Command " << CmdMapper::instance()->getKey(getType())
       << " failed to create model " << name;
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  G_Model().reset(model);
}

}
