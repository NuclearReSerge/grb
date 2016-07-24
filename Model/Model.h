#include "Model/ModelMapper.h"
#include "Model/ModelCmdMapper.h"

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

  type::ModelType getType() const;
  std::mt19937_64& getGenerator();
  std::size_t getNumberOfEntries() const;
  bool isConfigured() const;

  bool parse(type::ModelCmdType cmd, std::list<std::string>& tokens);
  void generate(Catalog& catalog);
  std::string help();

protected:
  virtual bool doParse(type::ModelCmdType cmd, std::list<std::string>& tokens) = 0;
  virtual void doGenerate(Catalog& catalog) = 0;
  virtual std::string doHelp() = 0;

  void init();
  void setNumberOfEntries(const std::size_t entries);
  void setConfigured(const bool configured = true);

private:
  type::ModelType _type;
  std::mt19937_64 _generator;
  std::size_t _entries;
  bool _configured;
};

}
