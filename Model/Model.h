#include "Model/ModelType.h"
#include "Model/ModelCmdType.h"

#include <list>
#include <random>
#include <string>

#pragma once

namespace grb
{

class Catalog;

class Model
{
public:
  Model(type::ModelType type = type::UNDEFINED_MODEL)
    : _type(type), _entries(0), _configured(false)
  {
    std::random_device hwGen;
    std::seed_seq seedSeq{hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen()};
    _generator.seed(seedSeq);
  }

  virtual ~Model() = default;

  type::ModelType getType() const
  {
    return _type;
  }

  std::mt19937_64& getGenerator()
  {
    return _generator;
  }

  std::size_t getNumberOfEntries() const
  {
    return _entries;
  }

  bool isConfigured() const
  {
    return _configured;
  }

  bool parse(type::ModelCmdType cmd, std::list<std::string>& tokens)
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

  void generate(Catalog& catalog)
  {
    doGenerate(catalog);
  }

  std::string help()
  {
    return doHelp();
  }

protected:
  virtual bool doParse(type::ModelCmdType cmd, std::list<std::string>& tokens) = 0;
  virtual void doGenerate(Catalog& catalog) = 0;
  virtual std::string doHelp() = 0;

  void setNumberOfEntries(const std::size_t entries)
  {
    _entries = entries;
  }

  void setConfigured(const bool configured = true)
  {
    _configured = configured;
  }

private:
  type::ModelType _type;
  std::mt19937_64 _generator;
  std::size_t _entries;
  bool _configured;
};

} // namespace grb
