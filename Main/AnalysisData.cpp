#include "Main/AnalysisData.h"

#include "Analyzer/Analyzer.h"
#include "Catalog/Catalog.h"
#include "Correlation/Correlation.h"
#include "Database/Database.h"
#include "Filter/Filter.h"
#include "Model/Model.h"

#include <memory>

namespace grb
{

namespace
{

std::unique_ptr<Analyzer> _analyzer;
std::unique_ptr<Correlation> _correlation;
std::unique_ptr<Catalog> _catalogData;
std::unique_ptr<Catalog> _catalogModel;
std::unique_ptr<Database> _database;
std::unique_ptr<Filter> _filter;
std::unique_ptr<Model> _model;

} // namespace

namespace internal
{

Analyzer*
AnalysisData::getAnalyzer()
{
  return _analyzer.get();
}

Correlation*
AnalysisData::getCorrelation()
{
  return _correlation.get();
}

Catalog*
AnalysisData::getCatalogData()
{
  return _catalogData.get();
}

Catalog*
AnalysisData::getCatalogModel()
{
  return _catalogModel.get();
}

Database*
AnalysisData::getDatabase()
{
  return _database.get();
}

Filter*
AnalysisData::getFilter()
{
  return _filter.get();
}

Model*
AnalysisData::getModel()
{
  return _model.get();
}

void
AnalysisData::setAnalyzer(Analyzer* analyzer)
{
  _analyzer.reset(analyzer);
}

void
AnalysisData::setCorrelation(Correlation* correlation)
{
  _correlation.reset(correlation);
}

void
AnalysisData::setCatalogData(Catalog* catalog)
{
  _catalogData.reset(catalog);
}

void
AnalysisData::setCatalogModel(Catalog* catalog)
{
  _catalogModel.reset(catalog);
}

void
AnalysisData::setDatabase(Database* database)
{
  _database.reset(database);
}

void
AnalysisData::setFilter(Filter* filter)
{
  _filter.reset(filter);
}

void
AnalysisData::setModel(Model* model)
{
  _model.reset(model);
}

void
AnalysisData::clear()
{
  _analyzer.reset(nullptr);
  _correlation.reset(nullptr);
  _catalogData.reset(nullptr);
  _catalogModel.reset(nullptr);
  _database.reset(nullptr);
  _filter.reset(nullptr);
  _model.reset(nullptr);
}

} // namespace internal
} // namespace grb
