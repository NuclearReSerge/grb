#include "Tools/Parser.h"
#include "test/CatalogEntryMock.h"
#include "test/DataBaseFormatMock.h"

#include "gtest/gtest.h"
#include <sstream>

using namespace ::testing;

namespace grb
{
namespace test
{

struct TypeAndValue
{
  type::ColumnType column;
  bool required;
  type::ValueType value;
  std::string raw;
};

typedef std::vector<TypeAndValue> TypeValueVector;

namespace
{
const TypeValueVector DEFAULT_ROW
{
  { type::COLUMN_TEST_FLAG,          true, type::FLAG,          "N" },
  { type::COLUMN_TEST_INTEGER,       true, type::INTEGER,       "9999" },
  { type::COLUMN_TEST_INDEX,         true, type::INDEX,         "NAME_LIST_FIRST" },
  { type::COLUMN_TEST_INTEGER_RANGE, true, type::INTEGER_RANGE, "9999-9999" },
  { type::COLUMN_TEST_INDEX_LIST,    true, type::INDEX_LIST,    "NAME_LIST_FIRST,NAME_LIST_LAST" },
  { type::COLUMN_TEST_FLOAT,         true, type::FLOAT,         "9999.9999" },
  { type::COLUMN_TEST_TIMEPOINT,     true, type::TIMEPOINT,     "0.0" }, // Julian
  { type::COLUMN_TEST_COORDINATE,    true, type::COORDINATE,    "0.0" },
  { type::COLUMN_TEST_STRING,        true, type::STRING,        "STRING" },
  { type::COLUMN_TEST_STRING_LIST,   true, type::STRING_LIST,   "STRING1,STRING2" }
};
}

class ParserTest : public Test
{
protected:
  void SetUp()
  {
    _parser = nullptr;
    _catalog = new Catalog(type::CATALOG_TEST);
    _format = new DataBaseFormatMock;
    _stream = new std::stringstream;

    _format->initialize();

  }

  void TearDown()
  {
    delete _stream;
    delete _format;
    delete _catalog;
    delete _parser;
  }

  void stringsToStream(TypeValueVector& tvv)
  {
    for(const TypeAndValue& tv : tvv)
    {
      std::size_t pos = tv.column;
      bool req = tv.required;
      _format->setColumnRequired(pos, req);
      *_stream << tv.raw << "|";
    }
  }

  void tryToParseFile(std::string& filename,
                      bool isThrowExpected = false)
  {
    bool isThrown = false;
    try
    {
      _parser = new Parser(filename, _format, _catalog);
    }
    catch (const Exception& exc)
    {
      isThrown = true;
      std::cout << exc.what()<< std::endl;
    }
    ASSERT_EQ(isThrowExpected, isThrown);
  }

  void tryToParseStream(std::size_t linesExpected = 1,
                        bool isThrowExpected = false)
  {
    std::size_t linesParsed = linesExpected;
    bool isThrown = false;
    try
    {
      _parser = new Parser(_stream, _format, _catalog);
      linesParsed = _parser->parse();
    }
    catch (const Exception& exc)
    {
      isThrown = true;
      std::cout << exc.what()<< std::endl;
    }
    ASSERT_EQ((std::size_t) linesExpected, (std::size_t) linesParsed);
    ASSERT_EQ(isThrowExpected, isThrown);
  }

  std::stringstream* _stream;
  Catalog* _catalog;
  DataBaseFormatMock* _format;
  Parser* _parser;
};

TEST_F(ParserTest, Constructor_NoSuchFile)
{
  std::string filename = "unknown.file";
  tryToParseFile(filename, true);
}

TEST_F(ParserTest, Constructor_FileExists)
{
  std::string filename = __FILE__;
  tryToParseFile(filename, false);
}

TEST_F(ParserTest, Constructor_StreamIsNull)
{
  delete _stream;
  _stream = nullptr;
  tryToParseStream(0, true);
}

TEST_F(ParserTest, Constructor_StreamIsEmpty)
{
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_EmptyLine)
{
  *_stream << "#" << std::endl;
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DelimitersOnly)
{
  TypeValueVector line = DEFAULT_ROW;
  for (auto& tv : line)
  {
    tv.required = false;
    tv.raw.clear();
  }
  stringsToStream(line);

  tryToParseStream();
}

TEST_F(ParserTest, parse_DelimitersWhitespaceOnly)
{
  TypeValueVector line = DEFAULT_ROW;
  for (auto& tv : line)
  {
    tv.required = false;
    tv.raw = "  ";
  }
  stringsToStream(line);

  tryToParseStream();
}

TEST_F(ParserTest, parse_DefaultRow)
{
  TypeValueVector line = DEFAULT_ROW;
  stringsToStream(line);

  tryToParseStream();
}

TEST_F(ParserTest, parse_Flag_Yes)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::FLAG;
  line[col].raw = "Y";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(true, *_catalog->get().front()->getFlag(line[col].column));
}

TEST_F(ParserTest, parse_Flag_No)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::FLAG;
  line[col].raw = "N";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(false, *_catalog->get().front()->getFlag(line[col].column));
}

TEST_F(ParserTest, parse_Flag_Invalid)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::FLAG;
  line[col].raw = "INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Flag_Invalid_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::FLAG;
  line[col].raw = "INVALID";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
}

TEST_F(ParserTest, parse_Flag_Empty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::FLAG;
  line[col].raw.clear();
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Integer_Min)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER;
  line[col].raw = "0";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(0, *_catalog->get().front()->getInteger(line[col].column));
}

TEST_F(ParserTest, parse_Integer_Max)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER;
  line[col].raw = "4294967295";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(4294967295, *_catalog->get().front()->getInteger(line[col].column));
}

TEST_F(ParserTest, parse_Integer_Negative)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER;
  line[col].raw = "-1";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Integer_Negative_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER;
  line[col].raw = "-1";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
}

TEST_F(ParserTest, parse_Integer_Invalid)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER;
  line[col].raw = "INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Integer_Invalid_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER;
  line[col].raw = "INVALID";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
}


TEST_F(ParserTest, parse_Integer_Empty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER;
  line[col].raw = "";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Index)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INDEX;
  line[col].raw = "NAME_LIST_LAST";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(1, *_catalog->get().front()->getIndex(line[col].column));
}

TEST_F(ParserTest, parse_Index_Invalid)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INDEX;
  line[col].raw = "INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Index_Invalid_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INDEX;
  line[col].raw = "INVALID";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
}

TEST_F(ParserTest, parse_Index_Empty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INDEX;
  line[col].raw = "";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_IntegerRange_Min)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER_RANGE;
  line[col].raw = "0-1";
  stringsToStream(line);

  tryToParseStream();
  type::IntegerRange* range = _catalog->get().front()->getIntegerRange(line[col].column);
  ASSERT_EQ(2, range->size());
  ASSERT_EQ(0, (*range)[0]);
  ASSERT_EQ(1, (*range)[1]);
}

TEST_F(ParserTest, parse_IntegerRange_Max)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER_RANGE;
  line[col].raw = "4294967294-4294967295";
  stringsToStream(line);

  tryToParseStream();
  type::IntegerRange* range = _catalog->get().front()->getIntegerRange(line[col].column);
  ASSERT_EQ(2, range->size());
  ASSERT_EQ(4294967294, (*range)[0]);
  ASSERT_EQ(4294967295, (*range)[1]);
}

TEST_F(ParserTest, parse_IntegerRange_Invalid)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER_RANGE;
  line[col].raw = "INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_IntegerRange_Invalid_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER_RANGE;
  line[col].raw = "INVALID";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
}

TEST_F(ParserTest, parse_IntegerRange_OneNumber)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER_RANGE;
  line[col].raw = "0";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_IntegerRange_OneNumber_Negative)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER_RANGE;
  line[col].raw = "-1";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_IntegerRange_TwoNumber_Negative)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER_RANGE;
  line[col].raw = "-1--2";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_IntegerRange_ThreeNumber)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = type::INTEGER_RANGE;
  line[col].raw = "0-1-2";
  stringsToStream(line);

  tryToParseStream(0, true);
}



/*
INDEX_LIST,
FLOAT,
TIMEPOINT,
COORDINATE,
STRING,
STRING_LIST,
*/

} // namespace test
} // namespace grb
