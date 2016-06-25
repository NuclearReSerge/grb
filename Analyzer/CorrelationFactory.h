#include "Common/Global.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class Correlation;

class CorrelationFactoryType
{
public:
  virtual Correlation* create(type::CorrelationType corrType);

protected:
  friend class Singleton<CorrelationFactoryType>;
  CorrelationFactoryType();
};

typedef Singleton<CorrelationFactoryType> CorrelationFactory;

}
