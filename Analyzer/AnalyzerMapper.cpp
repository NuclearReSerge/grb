#include "Analyzer/AnalyzerMapper.h"

namespace
{

const std::vector<std::string> ANALYSER_NAMES
{
  "grbcat-analyzer",

  // LAST
  "undefined-analyzer"
};

} // namespace


namespace grb
{
namespace mapper
{

const std::vector<std::string>& AnalyzerMapper::getList() const
{
  return ANALYSER_NAMES;
}

} // namespace mapper
} // namespace grb
