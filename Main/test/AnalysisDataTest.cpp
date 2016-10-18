#include "Main/AnalysisData.h"

#include "test/Mock/AnalyzerMock.h"
#include "test/Mock/CatalogMock.h"
#include "test/Mock/CorrelationMock.h"
#include "test/Mock/FilterMock.h"
#include "test/Mock/ModelMock.h"
#include <gtest/gtest.h>

namespace testing
{

class AnalysisDataTest : public Test
{
protected:
  grb::Analyzer* _analyzer;
  grb::Catalog* _catalogD;
  grb::Catalog* _catalogM;
  grb::Correlation* _correlation;
  grb::Filter* _filter;
  grb::Model* _model;
};

TEST_F(AnalysisDataTest, SetGetAnalyzer)
{
  _analyzer = new grb::AnalyzerMock(grb::type::UNDEFINED_ANALYZER);
  grb::AnalysisData::instance()->setAnalyzer(_analyzer);
  ASSERT_EQ(_analyzer, grb::AnalysisData::instance()->getAnalyzer());
  grb::AnalysisData::instance()->setAnalyzer(nullptr);
}

TEST_F(AnalysisDataTest, SetGetCatalogData)
{
  _catalogD = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
  grb::AnalysisData::instance()->setCatalogData(_catalogD);
  ASSERT_EQ(_catalogD, grb::AnalysisData::instance()->getCatalogData());
  grb::AnalysisData::instance()->setCatalogData(nullptr);
}

TEST_F(AnalysisDataTest, SetGetCatalogModel)
{
  _catalogM = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
  grb::AnalysisData::instance()->setCatalogModel(_catalogM);
  ASSERT_EQ(_catalogM, grb::AnalysisData::instance()->getCatalogModel());
  grb::AnalysisData::instance()->setCatalogModel(nullptr);
}

TEST_F(AnalysisDataTest, SetGetCorrelation)
{
  _correlation = new grb::CorrelationMock(grb::type::UNDEFINED_CORRELATION);
  grb::AnalysisData::instance()->setCorrelation(_correlation);
  ASSERT_EQ(_correlation, grb::AnalysisData::instance()->getCorrelation());
  grb::AnalysisData::instance()->setCorrelation(nullptr);
}

TEST_F(AnalysisDataTest, SetGetFilter)
{
  _filter = new grb::FilterMock(grb::type::UNDEFINED_FILTER);
  grb::AnalysisData::instance()->setFilter(_filter);
  ASSERT_EQ(_filter, grb::AnalysisData::instance()->getFilter());
  grb::AnalysisData::instance()->setFilter(nullptr);
}

TEST_F(AnalysisDataTest, SetGetModel)
{
  _model = new grb::ModelMock(grb::type::UNDEFINED_MODEL);
  grb::AnalysisData::instance()->setModel(_model);
  ASSERT_EQ(_model, grb::AnalysisData::instance()->getModel());
  grb::AnalysisData::instance()->setModel(nullptr);
}

TEST_F(AnalysisDataTest, clear)
{
  _analyzer = new grb::AnalyzerMock(grb::type::UNDEFINED_ANALYZER);
  grb::AnalysisData::instance()->setAnalyzer(_analyzer);
  _catalogD = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
  grb::AnalysisData::instance()->setCatalogData(_catalogD);
  _catalogM = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
  grb::AnalysisData::instance()->setCatalogModel(_catalogM);
  _correlation = new grb::CorrelationMock(grb::type::UNDEFINED_CORRELATION);
  grb::AnalysisData::instance()->setCorrelation(_correlation);
  _filter = new grb::FilterMock(grb::type::UNDEFINED_FILTER);
  grb::AnalysisData::instance()->setFilter(_filter);
  _model = new grb::ModelMock(grb::type::UNDEFINED_MODEL);
  grb::AnalysisData::instance()->setModel(_model);

  grb::AnalysisData::instance()->clear();

  ASSERT_EQ(nullptr, grb::AnalysisData::instance()->getAnalyzer());
  ASSERT_EQ(nullptr, grb::AnalysisData::instance()->getCatalogData());
  ASSERT_EQ(nullptr, grb::AnalysisData::instance()->getCatalogModel());
  ASSERT_EQ(nullptr, grb::AnalysisData::instance()->getCorrelation());
  ASSERT_EQ(nullptr, grb::AnalysisData::instance()->getFilter());
  ASSERT_EQ(nullptr, grb::AnalysisData::instance()->getModel());
}

} // namespace testing
