#include "Filter/FilterFactory.h"

#include "Filter/FilterNone.h"

namespace grb
{

namespace factory
{

Filter*
FilterFactory::create(type::FilterType type)
{
  switch (type)
  {
    case type::FILTER_NONE:
      return new FilterNone;
    default:
      break;
  }
  return nullptr;
}

Filter*
FilterFactory::create(const std::string& name)
{
  type::FilterType type;
  try
  {
    type = FilterMapper::instance()->getValue(name);
  }
  catch (Exception& exc)
  {
    return nullptr;
  }
  return create(type);
}

}

}
