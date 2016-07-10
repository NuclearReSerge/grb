#include "Model/ModelMapper.h"

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
  Model(type::ModelType type = type::UNDEFINED_MODEL);
  virtual ~Model();

  type::ModelType getType() const
  {
    return _type;
  }

  static std::string getName(type::ModelType type);

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

  virtual bool parse(std::list<std::string>& tokens) = 0;
  virtual void generate(Catalog& catalog) = 0;

protected:
  void init();

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

}
