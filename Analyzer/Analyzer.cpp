#include "Analyzer/Analyzer.h"

#include "Analyzer/AnalyzerCmdMapper.h"
#include "Common/Exception.h"
#include "Correlation/Correlation.h"
#include "Data/Catalog.h"
#include "Main/AnalysisData.h"

namespace grb
{

bool
Analyzer::parse(std::list<std::string>& tokens)
{
  if (tokens.empty())
  {
    return false;
  }

  std::string cmdName = tokens.front();
  tokens.pop_front();
  try
  {
    _cmdType = AnalyzerCmdMapper::instance()->getValue(cmdName);
  }
  catch (Exception&)
  {
    std::stringstream ss;
    ss << "Analyzer failed at parsing. Command '"
       << cmdName
       << "' unknown." << std::endl;
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str());
    throw exc;
  }

  if (!doParse(tokens))
  {
    std::stringstream ss;
    ss << "Analyzer failed at parsing. Command '"
       << AnalyzerCmdMapper::instance()->getKey(getCmdType())
       << "'." << std::endl;
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str());
    throw exc;
  }

  return true;
}

void
Analyzer::execute()
{
  doExecute();
}

} // namespace grb
