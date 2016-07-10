#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum CorrelationType
{
  CORRELATION_GRBCAT_DTDARC,

  // LAST
  UNDEFINED_CORRELATION
};

}

namespace mapper
{

class CorrelationMapper : public Mapper<type::CorrelationType>
{
public:
  CorrelationMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::CorrelationMapper> CorrelationMapper;

}
