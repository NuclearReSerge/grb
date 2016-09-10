#include "Analyzer/AnalyzerType.h"

#include <list>
#include <string>

#pragma once

namespace grb
{

class Analyzer
{
public:
  Analyzer(type::AnalyzerType type = type::UNDEFINED_ANALYZER)
    : _type(type), _configured(false)
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

  virtual bool parse(std::list<std::string>& tokens) = 0;
  virtual void run() = 0;

protected:
  void setConfigured(const bool configured = true)
  {
    _configured = configured;
  }

private:
  type::AnalyzerType _type;
  bool _configured;
};

} // namespace grb
