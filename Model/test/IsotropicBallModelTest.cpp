#include "Model/IsotropicBallModel.h"

#include "test/Mock/CatalogMock.h"
#include "test/Mock/CatalogEntryMock.h"
#include "test/Mock/MockHelper.h"

#include <gmock/gmock.h>

namespace testing
{

class IsotropicBallModelTest : public Test
{
protected:
  void callParseAndExecute()
  {
    try
    {
      _result = _model.parse(_cmd, _tokens);
      _model.execute(_cmd);
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }
  void callGenerate(grb::Catalog& catalog)
  {
    try
    {
       _model.generate(catalog);
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  grb::IsotropicBallModel _model;
  grb::type::ModelCmdType _cmd = grb::type::UNDEFINED_MODEL_CMD;
  double _min = -1.0;
  double _max = 2.0;
  std::list<std::string> _tokens { "(", "-1.0", ",", "2.0", ")" };
  bool _result = false;
  bool _thrown = false;
};

TEST_F(IsotropicBallModelTest, init)
{
  ASSERT_EQ(grb::type::ISOTROPIC_BALL, _model.getType());
  ASSERT_DOUBLE_EQ(0.0, _model.getTimeRange().a());
  ASSERT_DOUBLE_EQ(1.0, _model.getTimeRange().b());
  ASSERT_DOUBLE_EQ(0.0, _model.getRadiusRange().a());
  ASSERT_DOUBLE_EQ(1.0, _model.getRadiusRange().b());
  ASSERT_DOUBLE_EQ(0.0, _model.getPhiRange().a());
  ASSERT_DOUBLE_EQ(2.0 * M_PIl, _model.getPhiRange().b());
  ASSERT_DOUBLE_EQ(-M_PI_2l, _model.getThetaRange().a());
  ASSERT_DOUBLE_EQ(M_PI_2l, _model.getThetaRange().b());
}

TEST_F(IsotropicBallModelTest, ParseAnExecute_SetTime)
{
  _cmd = grb::type::MODEL_SET_TIME;

  callParseAndExecute();

  ASSERT_TRUE(_result);
  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_tokens.empty());
  ASSERT_DOUBLE_EQ(_min, _model.getTimeRange().a());
  ASSERT_DOUBLE_EQ(_max, _model.getTimeRange().b());
}

TEST_F(IsotropicBallModelTest, ParseAnExecute_SetRadius)
{
  _cmd = grb::type::MODEL_SET_RADIUS;

  callParseAndExecute();

  ASSERT_TRUE(_result);
  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_tokens.empty());
  ASSERT_DOUBLE_EQ(_min, _model.getRadiusRange().a());
  ASSERT_DOUBLE_EQ(_max, _model.getRadiusRange().b());
}

TEST_F(IsotropicBallModelTest, ParseAnExecute_SetPhi)
{
  _cmd = grb::type::MODEL_SET_PHI;

  callParseAndExecute();

  ASSERT_TRUE(_result);
  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_tokens.empty());
  ASSERT_DOUBLE_EQ(_min, _model.getPhiRange().a());
  ASSERT_DOUBLE_EQ(_max, _model.getPhiRange().b());
}

TEST_F(IsotropicBallModelTest, ParseAnExecute_SetTheta)
{
  _cmd = grb::type::MODEL_SET_THETA;

  callParseAndExecute();

  ASSERT_TRUE(_result);
  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_tokens.empty());
  ASSERT_DOUBLE_EQ(_min, _model.getThetaRange().a());
  ASSERT_DOUBLE_EQ(_max, _model.getThetaRange().b());
}

TEST_F(IsotropicBallModelTest, ParseAnExecute_EmptyTokens)
{
  _tokens.clear();
  callParseAndExecute();

  ASSERT_FALSE(_result);
}

TEST_F(IsotropicBallModelTest, ParseAnExecute_WrongRangeFormat)
{
  _cmd = grb::type::MODEL_SET_RADIUS;
  _tokens.clear();
  _tokens.push_front("(-1.0,2.0)");
  callParseAndExecute();

  ASSERT_TRUE(_thrown);
  ASSERT_FALSE(_tokens.empty());
}

TEST_F(IsotropicBallModelTest, ParseAnExecute_UnhandledCommand)
{
  callParseAndExecute();

  ASSERT_FALSE(_result);
  ASSERT_FALSE(_tokens.empty());
}

TEST_F(IsotropicBallModelTest, ParseAnExecute_SetCatalogType_ValidType)
{
  _cmd = grb::type::MODEL_SET_CATALOG_TYPE;
  _tokens.clear();
  _tokens.push_front("undefined-catalog");

  callParseAndExecute();

  ASSERT_TRUE(_result);
  ASSERT_FALSE(_thrown);
  ASSERT_TRUE(_tokens.empty());
}

TEST_F(IsotropicBallModelTest, ParseAnExecute_SetCatalogType_WrongType)
{
  _cmd = grb::type::MODEL_SET_CATALOG_TYPE;
  _tokens.clear();
  _tokens.push_front("catalog-name");

  callParseAndExecute();

  ASSERT_TRUE(_thrown);
  ASSERT_FALSE(_tokens.empty());
}

TEST_F(IsotropicBallModelTest, help)
{
  _model.help();
}

TEST_F(IsotropicBallModelTest, generate_WrongCatalogTypeProvided)
{
  grb::CatalogMock catalog(grb::type::GRBCAT);

  callGenerate(catalog);
  ASSERT_TRUE(_thrown);
}

TEST_F(IsotropicBallModelTest, generate_CatalogEntryNotCreated)
{
  grb::CatalogMock catalog(grb::type::UNDEFINED_CATALOG);

  _model.setNumberOfEntries(2);

  callGenerate(catalog);
  ASSERT_TRUE(_thrown);
}
/*
// include this test when more catalog types will be available
TEST_F(IsotropicBallModelTest, generate_WrongCatalogEntryCreated)
{
  grb::CatalogMock catalog(grb::type::GRBCAT);

  _model.setNumberOfEntries(2);

  callGenerate(catalog);
  ASSERT_TRUE(_thrown);
}
*/
TEST_F(IsotropicBallModelTest, generate_Positive)
{
  grb::CatalogMock catalog(grb::type::GRBCAT);

  _cmd = grb::type::MODEL_SET_CATALOG_TYPE;
  _tokens.clear();
  _tokens.push_front("grbcat");
  _model.parse(_cmd, _tokens);
  _model.execute(_cmd);
  _model.setNumberOfEntries(2);

  callGenerate(catalog);
  ASSERT_EQ(2, catalog.getEntries().size());
}

} // namespace testing
