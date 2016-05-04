#include <memory>
#include <string>

#pragma once

namespace grb
{

class Catalog;

class Analyzer
{
public:
  Analyzer();
  virtual ~Analyzer();

  Catalog* getCatalog();
  void setCatalog(Catalog* catalog);

  virtual void execute(const std::string& subcommand) = 0;

private:
  std::unique_ptr<Catalog> _catalog;
};

}
