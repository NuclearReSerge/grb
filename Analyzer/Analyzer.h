#include <memory>

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

private:
  std::unique_ptr<Catalog> _catalog;
};

}
