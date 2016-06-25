#include <list>
#include <memory>
#include <string>

#pragma once

namespace grb
{

class Catalog;
class ModelBase;

class Analyzer
{
public:
  Analyzer();
  virtual ~Analyzer();

  virtual bool parse(std::list<std::string>& subcmd) = 0;
  virtual void run() = 0;
};

}
