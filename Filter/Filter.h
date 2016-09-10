#include "Filter/FilterMapper.h"

#pragma once

namespace grb
{

class Filter
{
public:
  Filter(type::FilterType type = type::UNDEFINED_FILTER)
    : _type(type)
  {
  }

  virtual ~Filter() = default;

  type::FilterType getType() const
  {
    return _type;
  }

private:
  type::FilterType _type;
};

} // namespace grb
