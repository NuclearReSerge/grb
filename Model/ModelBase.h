#include "Common/Global.h"
#include <list>
#include <random>
#include <string>

#pragma once

namespace grb
{

class Catalog;

class ModelBase
{
public:
  ModelBase(type::ModelType type = type::MODEL_TYPE_UNDEFINED);
  virtual ~ModelBase();

  type::ModelType getType() const;
  std::mt19937_64& getGenerator();

  virtual bool parse(std::list<std::string>& subcmd) = 0;
  virtual void generate(Catalog& catalog, std::size_t entries) = 0;

protected:
  void init();

private:
  type::ModelType _type;
  std::mt19937_64 _generator;
};

}
