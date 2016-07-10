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

void
Model::init()
{
  std::random_device hwGen;
  std::seed_seq seedSeq{hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen(), hwGen()};
  _generator.seed(seedSeq);
}

}
