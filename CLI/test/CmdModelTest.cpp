#include "CLI/CmdModel.h"
#include "Main/AnalysisData.h"

#include "test/Mock/CatalogMock.h"
#include "test/Mock/ModelMock.h"
#include "test/Mock/MockHelper.h"

#include <gmock/gmock.h>

namespace testing
{

class CmdModelTest : public Test
{
protected:
  void TearDown()
  {
    grb::AnalysisData::instance()->setModel(nullptr);
    grb::AnalysisData::instance()->setCatalogData(nullptr);
    grb::AnalysisData::instance()->setCatalogData(nullptr);
  }

  void callParse()
  {
    try
    {
      _result = _cmd.parse(_tokens);
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  void callExecute()
  {
    try
    {
      _cmd.execute();
      ASSERT_TRUE(_cmd.wasExecuted());
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  bool _result = false;
  bool _thrown = false;
  grb::CmdModel _cmd;
  std::list<std::string> _tokens;
};

TEST_F(CmdModelTest, init)
{
  ASSERT_EQ(grb::type::CMD_MODEL, _cmd.getType());
}

TEST_F(CmdModelTest, parse_NoTokens)
{
  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, parse_UnknownSubcmd)
{
  _tokens.push_back("model-command");

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, parse_create_ModelAlreadyCreated)
{
  grb::AnalysisData::instance()->setModel(new grb::ModelMock(grb::type::UNDEFINED_MODEL));

  _tokens.push_back("create");

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, parse_create_NoModelName)
{
  _tokens.push_back("create");

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, parse_create_UnknownModel)
{
  _tokens.push_back("create");
  _tokens.push_back("model-name");

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, parse_create_ValidModel)
{
  _tokens.push_back("create");
  _tokens.push_back("undefined-model");

  callParse();

  ASSERT_TRUE(_result);
}

TEST_F(CmdModelTest, parse_generate)
{
  _tokens.push_back("generate");

  callParse();

  ASSERT_TRUE(_result);
}

TEST_F(CmdModelTest, parse_help_NoTokens_NoModel)
{
  _tokens.push_back("help");

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, parse_help_NoTokens_CurrentModel)
{
  grb::AnalysisData::instance()->setModel(new grb::ModelMock(grb::type::UNDEFINED_MODEL));

  _tokens.push_back("help");

  callParse();

  ASSERT_TRUE(_result);
}

TEST_F(CmdModelTest, parse_help_UnknownModel)
{
  _tokens.push_back("help");
  _tokens.push_back("model-name");

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, parse_help_ValidModel)
{
  _tokens.push_back("help");
  _tokens.push_back("undefined-model");

  callParse();

  ASSERT_TRUE(_result);
}

TEST_F(CmdModelTest, parse_ValidModelSubCommand_NoModel)
{
  _tokens.push_back("undefined-model-command");
  _tokens.push_back("undefined-model");

  callParse();

  ASSERT_FALSE(_result);
}

TEST_F(CmdModelTest, parse_ValidModelSubCommand_ModelParseFalse)
{
  _tokens.push_back("undefined-model-command");
  _tokens.push_back("undefined-model");

  grb::ModelMock* model = new grb::ModelMock(grb::type::UNDEFINED_MODEL);
  grb::AnalysisData::instance()->setModel(model);
  EXPECT_CALL(*model, doParse(_,_))
      .WillOnce(Return(false));

  callParse();

  ASSERT_FALSE(_result);
}

TEST_F(CmdModelTest, parse_ValidModelSubCommand_ModelParseTrue)
{
  _tokens.push_back("undefined-model-command");
  _tokens.push_back("undefined-model");

  grb::ModelMock* model = new grb::ModelMock(grb::type::UNDEFINED_MODEL);
  grb::AnalysisData::instance()->setModel(model);
  EXPECT_CALL(*model, doParse(_,_))
      .WillOnce(Return(true));

  callParse();

  ASSERT_FALSE(_result);
}

TEST_F(CmdModelTest, execute_create_ModelNotCreated)
{
  _tokens.push_back("create");
  _tokens.push_back("undefined-model");

  callParse();
  callExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, execute_create_ModelCreated)
{
  _tokens.push_back("create");
  _tokens.push_back("isotropic-sphere");

  callParse();
  callExecute();

  ASSERT_FALSE(_thrown);
  ASSERT_NE(nullptr, grb::AnalysisData::instance()->getModel());
}

TEST_F(CmdModelTest, execute_generate_NoModel)
{
  _tokens.push_back("generate");

  callParse();
  callExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, execute_generate_ModelNotConfigured)
{
  grb::ModelMock* model = new grb::ModelMock(grb::type::UNDEFINED_MODEL);
  grb::AnalysisData::instance()->setModel(model);

  _tokens.push_back("generate");

  callParse();
  callExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, execute_generate_NoCatalogData)
{
  grb::ModelMock* model = new grb::ModelMock(grb::type::UNDEFINED_MODEL);
  grb::AnalysisData::instance()->setModel(model);
  model->setConfigured();

  _tokens.push_back("generate");

  callParse();
  callExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, execute_generate_CatalogModel)
{
  grb::ModelMock* model = new grb::ModelMock(grb::type::UNDEFINED_MODEL);
  grb::CatalogMock* catalog = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
  grb::AnalysisData::instance()->setModel(model);
  grb::AnalysisData::instance()->setCatalogData(catalog);
  model->setConfigured();

  _tokens.push_back("generate");

  callParse();
  ASSERT_TRUE(_result);
  ASSERT_TRUE(_tokens.empty());

  EXPECT_CALL(*model, doGenerate(_))
       .Times(1);

  callExecute();

  ASSERT_FALSE(_thrown);
  ASSERT_NE(nullptr, grb::AnalysisData::instance()->getCatalogModel());
}

TEST_F(CmdModelTest, execute_help_ModelUnavailable)
{
  _tokens.push_back("help");
  _tokens.push_back("undefined-model");

  callParse();
  callExecute();

  ASSERT_FALSE(_thrown);
}

TEST_F(CmdModelTest, execute_help_ModelSpecific)
{
  _tokens.push_back("help");
  _tokens.push_back("isotropic-sphere");

  callParse();
  callExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, execute_help_CurrentModel)
{
  grb::ModelMock* model = new grb::ModelMock(grb::type::UNDEFINED_MODEL);
  grb::AnalysisData::instance()->setModel(model);
  EXPECT_CALL(*model, doHelp())
      .WillOnce(Return("Model help"));

  _tokens.push_back("help");

  callParse();
  callExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdModelTest, execute_ValidModelSubCommand_NoModel)
{
  _tokens.push_back("undefined-model-command");

  callParse();
  callExecute();
}

TEST_F(CmdModelTest, execute_ValidModelSubCommand_executed)
{
  _tokens.push_back("undefined-model-command");

  grb::ModelMock* model = new grb::ModelMock(grb::type::UNDEFINED_MODEL);
  grb::AnalysisData::instance()->setModel(model);
  EXPECT_CALL(*model, doParse(_,_))
      .WillOnce(Return(true));
  EXPECT_CALL(*model, doExecute(_))
      .Times(1);

  callParse();
  callExecute();
}

TEST_F(CmdModelTest, help_short)
{
  _cmd.help(grb::type::HELP_SHORT);
}

TEST_F(CmdModelTest, help_long)
{
  _cmd.help(grb::type::HELP_LONG);
}
} // namespace testing
