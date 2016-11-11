#include "Analyzer/AnalyzerCmdMapper.h"

namespace
{

const std::vector<std::string> ANALYSER_CMD_NAMES
{
  "create",
  "help",

  "list",
  //

  // LAST
  "undefined-analyzer-cmd"
};

} // namespace


namespace grb
{
namespace mapper
{

const std::vector<std::string>& AnalyzerCmdMapper::getList() const
{
  return ANALYSER_CMD_NAMES;
}

} // namespace mapper
} // namespace grb
