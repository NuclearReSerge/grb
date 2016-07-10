#include "Common/Singleton.h"
#include "Filter/Filter.h"

#pragma once

namespace grb
{

namespace factory
{

class FilterFactory
{
public:
  virtual Filter* create(type::FilterType type);
  virtual Filter* create(const std::string& name);
};

}

typedef Singleton<factory::FilterFactory> FilterFactory;

}
