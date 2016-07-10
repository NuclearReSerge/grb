#include "Analyzer/AnalyzerMapper.h"

#include <list>
#include <string>

#pragma once

namespace grb
{

class Analyzer
{
public:
  Analyzer(type::AnalyzerType type = type::UNDEFINED_ANALYZER);
  virtual ~Analyzer();

  type::AnalyzerType getType() const;
  bool isConfigured() const;

  virtual bool parse(std::list<std::string>& tokens) = 0;
  virtual void run() = 0;

protected:
  void setConfigured(const bool configured = true);

private:
  type::AnalyzerType _type;
  bool _configured;
};

}
