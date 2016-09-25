#include "Analyzer/AnalyzerType.h"

#include "Analyzer/AnalyzerCmdType.h"

#include <list>
#include <string>

#pragma once

namespace grb
{

class Analyzer
{
public:
  Analyzer(const type::AnalyzerType type = type::UNDEFINED_ANALYZER)
    : _type(type), _configured(false), _cmdType(type::UNDEFINED_ANALYZER_CMD)
  {
  }

  virtual ~Analyzer() = default;

  type::AnalyzerType getType() const
  {
    return _type;
  }

  bool isConfigured() const
  {
    return _configured;
  }

  void setConfigured(const bool configured = true)
  {
    _configured = configured;
  }

  type::AnalyzerCmdType getCmdType() const
  {
    return _cmdType;
  }

  bool parse(std::list<std::string>& tokens);
  void execute();

protected:
  virtual bool doParse(std::list<std::string>& tokens) = 0;
  virtual void doExecute() = 0;

private:
  const type::AnalyzerType _type;
  bool _configured;
  type::AnalyzerCmdType _cmdType;
};

} // namespace grb
