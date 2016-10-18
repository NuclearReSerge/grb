#include "Correlation/CorrelationMapper.h"

namespace
{

static std::vector<std::string> CORRELATION_NAMES
{
  "dtdarc",

  // LAST
  "undefined-correlation"
};

} // namespace

namespace grb
{
namespace mapper
{

const std::vector<std::string>& CorrelationMapper::getList() const
{
  return CORRELATION_NAMES;
}

} // namespace mapper
} // namespace grb
