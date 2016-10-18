#include "test/Mock/CatalogMock.h"
#include "test/Mock/ModelMock.h"

#include <gtest/gtest.h>

namespace
{

const std::list<std::string> ARGS =
{
  "ARG_1",
  "ARG_2",
  "ARG_3",
};

}

namespace testing
{

class ModelTest : public Test
{
public:
  bool doParseTrue(grb::type::ModelCmdType, std::list<std::string>&)
  {
    return true;
  }
  bool doParseFalse(grb::type::ModelCmdType, std::list<std::string>&)
  {
    return false;
  }

protected:
  void SetUp()
  {
    _args = ARGS;
  }

  bool _result { false };
  grb::ModelMock _model { grb::type::UNDEFINED_MODEL };
  std::list<std::string> _args;
};

TEST_F(ModelTest, initial)
{
  ASSERT_EQ(grb::type::UNDEFINED_MODEL, _model.getType());
  ASSERT_FALSE(_model.isConfigured());
  ASSERT_EQ((std::size_t) 0, _model.getNumberOfEntries());

  std::uniform_real_distribution<> dist;
  double val1 = dist(_model.getGenerator());
  double val2 = dist(_model.getGenerator());

  ASSERT_NE(std::fpclassify(std::abs(val1 - val2)), FP_ZERO);
}

TEST_F(ModelTest, setConfigured)
{
  _model.setConfigured();

  ASSERT_TRUE(_model.isConfigured());
}

TEST_F(ModelTest, setNumberOfEntries)
{
  std::size_t entries = 123456789;

  _model.setNumberOfEntries(entries);

  ASSERT_EQ(entries, _model.getNumberOfEntries());
}

TEST_F(ModelTest, parseCreate)
{
  ASSERT_NO_THROW(_result = _model.parse(grb::type::MODEL_CREATE, _args));

  ASSERT_FALSE(_result);
  ASSERT_FALSE(_args.empty());
}

TEST_F(ModelTest, parseHelp)
{
  ASSERT_NO_THROW(_result = _model.parse(grb::type::MODEL_HELP, _args));

  ASSERT_FALSE(_result);
  ASSERT_FALSE(_args.empty());
}

TEST_F(ModelTest, parseGenerate)
{
  ASSERT_NO_THROW(_result = _model.parse(grb::type::MODEL_GENERATE, _args));

  ASSERT_FALSE(_result);
  ASSERT_FALSE(_args.empty());
}

TEST_F(ModelTest, parseUndefinedModelCmd_Negative)
{
  EXPECT_CALL(_model, doParse(_, _))
      .Times(1)
      .WillOnce(Invoke(this, &ModelTest::doParseTrue));

  ASSERT_NO_THROW(_result = _model.parse(grb::type::UNDEFINED_MODEL_CMD, _args));

  ASSERT_TRUE(_result);
  ASSERT_NE(0, _args.size());
}

TEST_F(ModelTest, generate)
{
  grb::CatalogMock catalog(grb::type::UNDEFINED_CATALOG);
  EXPECT_CALL(_model, doGenerate(_))
      .Times(1);

  _model.generate(catalog);
}

TEST_F(ModelTest, execute)
{
  EXPECT_CALL(_model, doExecute(_))
      .Times(1);

  _model.execute(grb::type::UNDEFINED_MODEL_CMD);
}


TEST_F(ModelTest, help)
{
  EXPECT_CALL(_model, doHelp())
      .Times(1);

  _model.help();
}

} // namespace testing
