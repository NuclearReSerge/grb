#include "CLI/CmdDatabase.h"
#include "Main/AnalysisData.h"

#include "test/Mock/CatalogMock.h"
#include "test/Mock/DataBaseFormatMock.h"
#include "test/Mock/ParserMock.h"
#include "test/Mock/MockHelper.h"

#include <gmock/gmock.h>

namespace grb
{

class CmdDatabaseMock : public CmdDatabase
{
public:
  CmdDatabaseMock() = default;

  MOCK_METHOD1(getDbFormat, DataBaseFormat* (const type::DataBaseFormatType& dbType));
  MOCK_METHOD1(getCatalog, Catalog* (type::DataBaseFormatType dbType));
  MOCK_METHOD2(getParser, Parser* (DataBaseFormat& dbFormat, Catalog& catalog));
};

} //namespace grb


namespace testing
{

class CmdDatabaseTest : public Test
{
public:
  bool parseTrue()
  {
    return true;
  }
  bool parseFalse()
  {
    return false;
  }
  bool parseThrow()
  {
    grb::Exception exc(0, "parseThrow");
    throw exc;
  }

protected:
  void callParse()
  {
    try
    {
      _result = _cmdMock.parse(_tokens);
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
      _cmdMock.execute();
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  bool _result = false;
  bool _thrown = false;
  grb::CmdDatabaseMock _cmdMock;
  std::list<std::string> _tokens { "heasarc_grbcat.tdat" };
};

TEST_F(CmdDatabaseTest, init)
{
  ASSERT_EQ(grb::type::CMD_DATABASE, _cmdMock.getType());
}

TEST_F(CmdDatabaseTest, parse_empty)
{
  _tokens.clear();
  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdDatabaseTest, parse_noExtension)
{
  _tokens.clear();
  _tokens.push_back("filename-no-ext");
  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdDatabaseTest, parse_wrongExtension)
{
  _tokens.clear();
  _tokens.push_back("filename.ext");
  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdDatabaseTest, parse_wrongFilename)
{
  _tokens.clear();
  _tokens.push_back("filename.tdat");
  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdDatabaseTest, parse_wrongDbFormat)
{
  EXPECT_CALL(_cmdMock, getDbFormat(_))
      .WillOnce(Return(nullptr));

  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdDatabaseTest, parse_extraToken)
{
  grb::DataBaseFormat* format = new grb::DataBaseFormatMock(grb::type::UNDEFINED_DATABASE_FORMAT);

  EXPECT_CALL(_cmdMock, getDbFormat(_))
      .WillOnce(Return(format));

  _tokens.push_back("extra");
  callParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdDatabaseTest, parse_positive)
{
  grb::DataBaseFormat* format = new grb::DataBaseFormatMock(grb::type::UNDEFINED_DATABASE_FORMAT);

  EXPECT_CALL(_cmdMock, getDbFormat(_))
      .WillOnce(Return(format));

  callParse();

  ASSERT_TRUE(_result);
}

TEST_F(CmdDatabaseTest, execute_CatalogNotCreated)
{
  EXPECT_CALL(_cmdMock, getCatalog(_))
      .WillOnce(Return(nullptr));

  callExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdDatabaseTest, execute_ParserNotCreated)
{
  grb::Catalog* catalog = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
  grb::ParserMock* parser = nullptr;

  EXPECT_CALL(_cmdMock, getCatalog(_))
      .WillOnce(Return(catalog));

  EXPECT_CALL(_cmdMock, getParser(_, _))
      .WillOnce(Return(parser));

  callExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdDatabaseTest, execute_ParserThrows)
{
  grb::Catalog* catalog = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
  grb::ParserMock* parser = new grb::ParserMock();

  EXPECT_CALL(_cmdMock, getCatalog(_))
      .WillOnce(Return(catalog));
  EXPECT_CALL(_cmdMock, getParser(_, _))
      .WillOnce(Return(parser));
  EXPECT_CALL(*parser, parse())
      .WillOnce(Invoke(this, &CmdDatabaseTest::parseThrow));

  callExecute();

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdDatabaseTest, execute_ParseFalse)
{
  grb::Catalog* catalog = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
  grb::ParserMock* parser = new grb::ParserMock();

  EXPECT_CALL(_cmdMock, getCatalog(_))
      .WillOnce(Return(catalog));
  EXPECT_CALL(_cmdMock, getParser(_, _))
      .WillOnce(Return(parser));
  EXPECT_CALL(*parser, parse())
      .WillOnce(Invoke(this, &CmdDatabaseTest::parseFalse));

  callExecute();

  ASSERT_EQ(nullptr, grb::AnalysisData::instance()->getCatalogData());
}

TEST_F(CmdDatabaseTest, execute_ParseTrue)
{
  grb::Catalog* catalog = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
  grb::ParserMock* parser = new grb::ParserMock();

  EXPECT_CALL(_cmdMock, getCatalog(_))
      .WillOnce(Return(catalog));
  EXPECT_CALL(_cmdMock, getParser(_, _))
      .WillOnce(Return(parser));
  EXPECT_CALL(*parser, parse())
      .WillOnce(Invoke(this, &CmdDatabaseTest::parseTrue));

  callExecute();

  ASSERT_EQ(catalog, grb::AnalysisData::instance()->getCatalogData());
}

TEST_F(CmdDatabaseTest, help_short)
{
  _cmdMock.help(grb::type::HELP_SHORT);
}

TEST_F(CmdDatabaseTest, help_long)
{
  _cmdMock.help(grb::type::HELP_LONG);
}

} // namespace testing

namespace grb
{

class CmdDatabaseStub : public CmdDatabase
{
public:
  CmdDatabaseStub()
    : CmdDatabase()
  {
  }

  DataBaseFormat* getDbFormatStub(const type::DataBaseFormatType& dbType)
  {
    return getDbFormat(dbType);
  }

  Catalog* getCatalogStub(type::DataBaseFormatType dbType)
  {
    return getCatalog(dbType);
  }

  Parser* getParserStub(DataBaseFormat& dbFormat, Catalog& catalog)
  {
    return getParser(dbFormat, catalog);
  }

  bool filenameMappingStub(const std::string& filename)
  {
    return filenameMapping(filename);
  }
};

} // namespace grb

namespace testing
{

class CmdDatabaseStubTest : public Test
{
protected:
  bool _result = false;
  bool _thrown = false;
  grb::CmdDatabaseStub _cmdStub;
};

TEST_F(CmdDatabaseStubTest, getDbFormat_Negative)
{
  grb::DataBaseFormat* format = _cmdStub.getDbFormatStub(grb::type::UNDEFINED_DATABASE_FORMAT);

  ASSERT_EQ(nullptr, format);
}

TEST_F(CmdDatabaseStubTest, getDbFormat_Positive)
{
  grb::DataBaseFormat* format = _cmdStub.getDbFormatStub(grb::type::HEASARC_GRBCAT);

  ASSERT_NE(nullptr, format);
}

TEST_F(CmdDatabaseStubTest, getCatalog_Negative)
{
  grb::Catalog* catalog = nullptr;
  _cmdStub.filenameMappingStub("heasarc_grbcat.tdat");

  try
  {
    catalog = _cmdStub.getCatalogStub(grb::type::UNDEFINED_DATABASE_FORMAT);
  }
  catch (grb::Exception& exc)
  {
    _thrown = true;
    printWhat(exc);
  }

  ASSERT_TRUE(_thrown);
  ASSERT_EQ(nullptr, catalog);
}

TEST_F(CmdDatabaseStubTest, getCatalog_Positive)
{
  grb::Catalog* catalog = nullptr;

  ASSERT_NO_THROW(catalog = _cmdStub.getCatalogStub(grb::type::HEASARC_GRBCAT));

  ASSERT_FALSE(_thrown);
  ASSERT_NE(nullptr, catalog);
}

TEST_F(CmdDatabaseStubTest, getParser_ParserNotCreated)
{
  std::string filename("filename");
  grb::DataBaseFormatMock dbFormat(grb::type::UNDEFINED_DATABASE_FORMAT);
  grb::CatalogMock catalog(grb::type::UNDEFINED_CATALOG);

  _cmdStub.filenameMappingStub(filename);

  try
  {
    _cmdStub.getParserStub(dbFormat, catalog);
  }
  catch (grb::Exception& exc)
  {
    _thrown = true;
    printWhat(exc);
  }

  ASSERT_TRUE(_thrown);
}

TEST_F(CmdDatabaseStubTest, getParser_Positive)
{

  std::string filename("heasarc_grbcat.tdat");
  grb::DataBaseFormatMock dbFormat(grb::type::UNDEFINED_DATABASE_FORMAT);
  grb::CatalogMock catalog(grb::type::UNDEFINED_CATALOG);
  grb::Parser* parser = nullptr;

  _cmdStub.filenameMappingStub(filename);

  ASSERT_NO_THROW(parser = _cmdStub.getParserStub(dbFormat, catalog));

  parser->getNumberOfRows();
  ASSERT_FALSE(_thrown);
}

} // namespace testing
