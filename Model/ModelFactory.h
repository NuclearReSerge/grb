#include "Common/Singleton.h"
#include "Model/Model.h"

#pragma once

namespace grb
{

namespace factory
{

class ModelFactory
{
public:
  virtual Model* create(type::ModelType type);
  virtual Model* create(const std::string& name);
};

}

typedef Singleton<factory::ModelFactory> ModelFactory;

}

