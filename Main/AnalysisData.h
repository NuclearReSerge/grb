#pragma once

#include "Common/Singleton.h"

namespace grb
{

class Analyzer;
class Correlation;
class Catalog;
class Database;
class Filter;
class Model;

namespace internal
{

class AnalysisData
{
public:
  AnalysisData() = default;
  ~AnalysisData() = default;

  Analyzer* getAnalyzer();
  Correlation* getCorrelation();
  Catalog* getCatalogData();
  Catalog* getCatalogModel();
  Database* getDatabase();
  Filter* getFilter();
  Model* getModel();

  void setAnalyzer(Analyzer* analyzer);
  void setCorrelation(Correlation* correlation);
  void setCatalogData(Catalog* catalog);
  void setCatalogModel(Catalog* catalog);
  void setDatabase(Database* database);
  void setFilter(Filter* filter);
  void setModel(Model* model);

  void clear();
};

} // namespace internal

typedef Singleton<internal::AnalysisData> AnalysisData;

} // namespace grb
