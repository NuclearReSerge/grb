#include "Common/Singleton.h"
#include "Correlation/Correlation.h"

#pragma once

namespace grb
{

namespace factory
{

class CorrelationFactory
{
public:
  virtual Correlation* create(type::CorrelationType type);
  virtual Correlation* create(const std::string& name);
};

}

typedef Singleton<factory::CorrelationFactory> CorrelationFactory;

}
