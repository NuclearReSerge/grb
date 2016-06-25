#include "Common/Global.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class ModelBase;

class ModelFactoryType
{
public:
  virtual ModelBase* create(type::ModelType modelType);

protected:
  friend class Singleton<ModelFactoryType>;
  ModelFactoryType();
};

typedef Singleton<ModelFactoryType> ModelFactory;

}

