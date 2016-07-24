#include "Model/Model.h"

namespace grb
{

Model::Model(type::ModelType type)
  : _type(type), _entries(0), _configured(false)
{
  init();
}

Model::~Model()
{
}

type::ModelType
Model::getType() const
{
  return _type;
}

std::mt19937_64&
Model::getGenerator()
{
  return _generator;
}

std::size_t
Model::getNumberOfEntries() const
{
  return _entries;
}

bool
Model::isConfigured() const
{
  return _configured;
}

bool
Model::parse(type::ModelCmdType cmd, std::list<std::string>& tokens)
{
  switch (cmd)
  {
    case type::MODEL_CREATE:
    case type::MODEL_HELP:
    case type::MODEL_GENERATE:
    {
      tokens.clear();
      return true;
    }
    default:
      break;
  }
  return doParse(cmd, tokens);
}

void
Model::generate(Catalog& catalog)
{
  doGenerate(catalog);
}

std::string
Model::help()
{
  return doHelp();
}

void
Model::init()
{
  std::random_device hwGen;
  std::seed_seq seedSeq{hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen()};
  _generator.seed(seedSeq);
}

void
Model::setNumberOfEntries(const std::size_t entries)
{
  _entries = entries;
}

void
Model::setConfigured(const bool configured)
{
  _configured = configured;
}

}
