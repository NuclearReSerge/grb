#include "Analyzer/Analyzer.h"
#include "Data/Catalog.h"

namespace grb
{

Analyzer::Analyzer()
{

}

Analyzer::~Analyzer()
{
  _catalog.reset();
}

Catalog*
Analyzer::getCatalog()
{
  return _catalog.get();
}

void
Analyzer::setCatalog(Catalog* catalog)
{
  _catalog.reset(catalog);
}

}
