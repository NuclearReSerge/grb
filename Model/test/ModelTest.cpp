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

};

TEST_F(ModelTest, initial)
{
  grb::ModelMock model;

  ASSERT_EQ(grb::type::UNDEFINED_MODEL, model.getType());
  ASSERT_FALSE(model.isConfigured());
  ASSERT_EQ((std::size_t) 0, model.getNumberOfEntries());

  std::uniform_real_distribution<> dist;
  double val1 = dist(model.getGenerator());
  double val2 = dist(model.getGenerator());

  ASSERT_NE(std::fpclassify(std::abs(val1 - val2)), FP_ZERO);
}

TEST_F(ModelTest, setConfigured)
{
  grb::ModelMock model;

  model.setConfigured();

  ASSERT_TRUE(model.isConfigured());
}

TEST_F(ModelTest, setNumberOfEntries)
{
  grb::ModelMock model;
  std::size_t entries = 123456789;

  model.setNumberOfEntries(entries);

  ASSERT_EQ(entries, model.getNumberOfEntries());
}

TEST_F(ModelTest, parseCreate_Positive)
{
  grb::ModelMock model;

  EXPECT_CALL(model, doParse(_,_))
      .Times(1)
      .WillOnce(Invoke(this, &ModelTest::doParseTrue));

  bool res = false;
  std::list<std::string> args = ARGS;

  ASSERT_NO_THROW(res = model.parse(grb::type::MODEL_CREATE, args));
  ASSERT_TRUE(res);
  ASSERT_NE(0, args.size());
}

TEST_F(ModelTest, parseCreate_Negative)
{
  grb::ModelMock model;

  EXPECT_CALL(model, doParse(_, _))
      .Times(1)
      .WillOnce(Invoke(this, &ModelTest::doParseFalse));

  bool res = false;
  std::list<std::string> args = ARGS;

  ASSERT_NO_THROW(res = model.parse(grb::type::MODEL_CREATE, args));
  ASSERT_FALSE(res);
  ASSERT_NE(0, args.size());
}

TEST_F(ModelTest, parseHelp_Positive)
{
  grb::ModelMock model;
  std::list<std::string> args = ARGS;

  EXPECT_CALL(model, doParse(_, _))
      .Times(1)
      .WillOnce(Invoke(this, &ModelTest::doParseTrue));

  bool res = false;

  ASSERT_NO_THROW(res = model.parse(grb::type::MODEL_HELP, args));
  ASSERT_TRUE(res);
  ASSERT_NE(0, args.size());
}

TEST_F(ModelTest, parseHelp_Negative)
{
  grb::ModelMock model;
  std::list<std::string> args = ARGS;

  EXPECT_CALL(model, doParse(_, _))
      .Times(1)
      .WillOnce(Invoke(this, &ModelTest::doParseFalse));

  bool res = false;

  ASSERT_NO_THROW(res = model.parse(grb::type::MODEL_HELP, args));
  ASSERT_FALSE(res);
  ASSERT_NE(0, args.size());
}

TEST_F(ModelTest, parseGenerate_Positive)
{
  grb::ModelMock model;
  std::list<std::string> args = ARGS;

  EXPECT_CALL(model, doParse(_, _))
      .Times(0);

  bool res = false;

  ASSERT_NO_THROW(res = model.parse(grb::type::MODEL_GENERATE, args));
  ASSERT_TRUE(res);
  ASSERT_EQ(0, args.size());
}

TEST_F(ModelTest, parseUndefinedModelCmd_Negative)
{
  grb::ModelMock model;
  std::list<std::string> args = ARGS;

  EXPECT_CALL(model, doParse(_, _))
      .Times(1)
      .WillOnce(Invoke(this, &ModelTest::doParseTrue));

  bool res = false;

  ASSERT_NO_THROW(res = model.parse(grb::type::UNDEFINED_MODEL_CMD, args));
  ASSERT_TRUE(res);
  ASSERT_NE(0, args.size());
}

} // namespace testing
