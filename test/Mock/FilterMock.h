#include "Filter/Filter.h"

#include "gmock/gmock.h"

#pragma once

namespace grb
{

class FilterMock : public Filter
{
public:
  FilterMock(type::FilterType type)
    : Filter(type)
  {
  }
};

} // namespace grb
