#include "Filter/Filter.h"

namespace grb
{

Filter::Filter(type::FilterType type)
  : _type(type)
{
}

Filter::~Filter()
{
}

type::FilterType
Filter::getType() const
{
  return _type;
}

}
