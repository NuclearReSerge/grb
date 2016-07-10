#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum FilterType
{
  FILTER_NONE,

  // LAST
  UNDEFINED_FILTER
};

}

namespace mapper
{

class FilterMapper : public Mapper<type::FilterType>
{
public:
  FilterMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::FilterMapper> FilterMapper;

}

