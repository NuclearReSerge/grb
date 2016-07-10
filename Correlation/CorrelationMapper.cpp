#include "Correlation/CorrelationMapper.h"

namespace grb
{

namespace
{

static std::vector<std::string> CORRELATION_NAMES
{
  "correlation-grbcat-dtdarc",

  // LAST
  "undefined-correlation"
};

}

namespace mapper
{

CorrelationMapper::CorrelationMapper()
{
  initiate();
}

const std::vector<std::string>& CorrelationMapper::getList() const
{
  return CORRELATION_NAMES;
}

}

}
