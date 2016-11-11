#pragma once

#include "Common/BaseObject.h"
#include "Model/ModelType.h"
#include "Model/ModelCmdType.h"

#include <list>
#include <random>
#include <string>

namespace grb
{

class Catalog;

class Model : public BaseObject<type::ModelType, type::ModelCmdType>
{
public:
  typedef BaseObject<type::ModelType, type::ModelCmdType> Base;

  Model(type::ModelType type = type::UNDEFINED_MODEL)
    : Base(type), _entries(0), _configured(false)
  {
    std::random_device hwGen;
    std::seed_seq seedSeq { hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen() };
    _generator.seed(seedSeq);
  }

  std::mt19937_64& getGenerator()
  {
    return _generator;
  }

  std::size_t getNumberOfEntries() const
  {
    return _entries;
  }

  void setNumberOfEntries(const std::size_t entries)
  {
    _entries = entries;
  }

  bool isConfigured() const
  {
    return _configured;
  }

  void setConfigured(const bool configured = true)
  {
    _configured = configured;
  }

  void generate(Catalog& catalog)
  {
    doGenerate(catalog);
  }

protected:
  bool isCommandValid(type::ModelCmdType cmd)
  {
    switch (cmd)
    {
      case type::MODEL_CREATE:
      case type::MODEL_HELP:
      case type::MODEL_GENERATE:
        return false;
      default:
        return true;
    }
  }
  virtual void doGenerate(Catalog& catalog) = 0;

private:
  std::mt19937_64 _generator;
  std::size_t _entries;
  bool _configured;
};

} // namespace grb
