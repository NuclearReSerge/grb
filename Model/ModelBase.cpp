#include "Model/ModelBase.h"

namespace grb
{

ModelBase::ModelBase(type::ModelType type)
  : _type(type)
{
  init();
}

ModelBase::~ModelBase()
{
}

type::ModelType
ModelBase::getType() const
{
  return _type;
}

std::mt19937_64&
ModelBase::getGenerator()
{
  return _generator;
}

void
ModelBase::init()
{
  std::random_device hwGen;
  std::seed_seq seedSeq{hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen()};
  _generator.seed(seedSeq);
}

}
