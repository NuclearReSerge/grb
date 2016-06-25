#include "CLI/CmdModel.h"

#include "CLI/CommandMapper.h"
#include "Common/GlobalName.h"
#include "Main/AnalysisData.h"
#include "Model/ModelFactory.h"
#include "Model/ModelBase.h"

#include <sstream>

namespace grb
{

namespace
{

const char* HELP_SHORT = " - theoretical model.";
const char* HELP_LONG = " <SUB_COMMAND>";

}

CmdModel::CmdModel(CommandLine& cli)
  : Cmd(cli, type::CMD_MODEL)
{

}

bool
CmdModel::doParse(std::list<std::string>& args)
{
  if (args.empty())
  {
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  help(type::HELP_LONG), PRETTY_FUNCTION);
    throw exc;
  }

  if (!G_Model().get())
  {
    modelNameMapping(args.front());
    args.pop_front();
  }
  G_Model().get()->parse(args);
  return true;
}

void
CmdModel::doExecute()
{

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
  type::ModelType type = type::MODEL_TYPE_UNDEFINED;

  for (int i = 0; i < type::MODEL_TYPE_UNDEFINED; ++i)
  {
    if (GlobalName::getModel((type::ModelType) i) == name)
      type = (type::ModelType) i;
  }

  ModelBase* model = ModelFactory::instance()->create(type);
  if (!model)
  {
    std::stringstream ss;
    ss << "Command " << CommandMapper::instance()->getKey(getType())
       << " failed to create model " << name;
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  G_Model().reset(model);
}

}
