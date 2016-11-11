#pragma once

#include "Common/BaseObject.h"
#include "Filter/FilterCmdType.h"
#include "Filter/FilterType.h"

namespace grb
{

typedef BaseObject<type::FilterType, type::FilterCmdType> FilterBase;

class Filter : public FilterBase
{
public:
  Filter(type::FilterType type = type::UNDEFINED_FILTER)
    : FilterBase(type)
  {
  }

protected:
  bool isCommandValid(type::FilterCmdType cmd)
  {
    switch (cmd)
    {
      case type::FILTER_CREATE:
      case type::FILTER_HELP:
      {
        return false;
      }
      default:
        return true;;
    }
  }

};

} // namespace grb
