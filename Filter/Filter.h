#include "Filter/FilterMapper.h"

#include <string>

#pragma once

namespace grb
{

class Filter
{
public:
  Filter(type::FilterType type = type::UNDEFINED_FILTER);
  virtual ~Filter();

  type::FilterType getType() const;

private:
  type::FilterType _type;
};

}
