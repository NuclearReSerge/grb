#include "Main/AnalysisData.h"

namespace grb
{

std::unique_ptr<Analyzer>&
G_Analyzer()
{
  static std::unique_ptr<Analyzer> _analyzer;
  return _analyzer;
}

std::unique_ptr<Correlation>&
G_Correlation()
{
  static std::unique_ptr<Correlation> _correlation;
  return _correlation;
}

std::unique_ptr<Catalog>&
G_CatalogData()
{
  static std::unique_ptr<Catalog> _catalog;
  return _catalog;
}

std::unique_ptr<Catalog>&
G_CatalogModel()
{
  static std::unique_ptr<Catalog> _catalog;
  return _catalog;
}

std::unique_ptr<Filter>& G_Filter()
{
  static std::unique_ptr<Filter> _filter;
  return _filter;
}

std::unique_ptr<Model>&
G_Model()
{
  static std::unique_ptr<Model> _model;
  return _model;
}

} // namespace grb
