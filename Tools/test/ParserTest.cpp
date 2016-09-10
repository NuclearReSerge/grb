#include "Data/Catalog.h"
#include "Tools/Parser.h"

#include "test/Mock/CatalogEntryMock.h"
#include "test/Mock/DataBaseFormatMock.h"

#include <gtest/gtest.h>
#include <sstream>

namespace
{

struct TypeAndValue
{
  grb::type::ColumnType column;
  bool required;
  grb::type::ValueType value;
  std::string raw;
};

typedef std::vector<TypeAndValue> TypeValueVector;


const TypeValueVector DEFAULT_ROW
{
  { grb::type::TEST_COLUMN_FLAG,          true, grb::type::FLAG,          "N" },
  { grb::type::TEST_COLUMN_INTEGER,       true, grb::type::INTEGER,       "9999" },
  { grb::type::TEST_COLUMN_INDEX,         true, grb::type::INDEX,         "NAME_LIST_FIRST" },
  { grb::type::TEST_COLUMN_INTEGER_RANGE, true, grb::type::INTEGER_RANGE, "9999-9999" },
  { grb::type::TEST_COLUMN_INDEX_LIST,    true, grb::type::INDEX_LIST,    "NAME_LIST_FIRST,NAME_LIST_LAST" },
  { grb::type::TEST_COLUMN_FLOAT,         true, grb::type::FLOAT,         "9999.9999" },
  { grb::type::TEST_COLUMN_STRING,        true, grb::type::STRING,        "STRING" },
  { grb::type::TEST_COLUMN_STRING_LIST,   true, grb::type::STRING_LIST,   "STRING1,STRING2" }
};

} // namespace

namespace testing
{

class ParserTest : public Test
{
protected:
  void SetUp()
  {
    _parser = nullptr;
    _stream = new std::stringstream;

    _format.initialize();

  }

  void TearDown()
  {
    delete _stream;
    delete _parser;
  }

  void stringsToStream(TypeValueVector& tvv)
  {
    for(const TypeAndValue& tv : tvv)
    {
      _format.setColumnFlag(tv.column, tv.required);
      *_stream << tv.raw << "|";
    }
  }

  void tryToParseFile(std::string& filename,
                      bool isThrowExpected = false)
  {
    bool isThrown = false;
    try
    {
      _parser = new grb::Parser(filename, _format, _catalog);
    }
    catch (const grb::Exception& exc)
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
      _parser = new grb::Parser(_stream, _format, _catalog);
      linesParsed = _parser->parse();
    }
    catch (const grb::Exception& exc)
    {
      isThrown = true;
      std::cout << exc.what()<< std::endl;
    }
    ASSERT_EQ(isThrowExpected, isThrown);
    ASSERT_EQ((std::size_t) linesExpected, (std::size_t) linesParsed);
    ASSERT_EQ((std::size_t) linesExpected, _catalog.getEntries().size());
  }

  grb::CatalogEntryMock& getCatalogEntry(std::size_t index = 0)
  {
    return * static_cast<grb::CatalogEntryMock*>(_catalog.getEntries()[index]);
  }

  std::stringstream* _stream;
  grb::Parser* _parser;
  grb::Catalog _catalog;
  grb::DataBaseFormatMock _format;
};

namespace constructor
{

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

}

namespace whitespace
{

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

}

namespace defaultrow
{

TEST_F(ParserTest, parse_DefaultRow)
{
  TypeValueVector line = DEFAULT_ROW;
  stringsToStream(line);

  tryToParseStream();
}

}

namespace formats
{

TEST_F(ParserTest, parse_Format_OneColumn)
{
  TypeValueVector line;
  TypeAndValue column { grb::type::TEST_COLUMN_FLAG, true, grb::type::FLAG, "N" };
  line.push_back(column);
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Format_OneLessColumn)
{
  TypeValueVector line = DEFAULT_ROW;
  line.pop_back();
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Format_OneMoreColumn)
{
  TypeValueVector line = DEFAULT_ROW;
  TypeAndValue column { grb::type::TEST_COLUMN_FLAG, true, grb::type::FLAG, "N" };
  line.push_back(column);

  stringsToStream(line);

  tryToParseStream(0, true);
}

}

namespace typeflag
{

TEST_F(ParserTest, parse_Flag_Yes)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLAG;
  line[col].raw = "Y";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(true, getCatalogEntry().getFlag());
}

TEST_F(ParserTest, parse_Flag_No)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLAG;
  line[col].raw = "N";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(false, getCatalogEntry().getFlag());
}

TEST_F(ParserTest, parse_Flag_Invalid)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLAG;
  line[col].raw = "INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Flag_Invalid_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLAG;
  line[col].raw = "INVALID";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(false, getCatalogEntry().getFlag());
}

TEST_F(ParserTest, parse_Flag_Empty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLAG;
  line[col].raw.clear();
  stringsToStream(line);

  tryToParseStream(0, true);
}

}

namespace typeinteger
{

TEST_F(ParserTest, parse_Integer_Min)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER;
  line[col].raw = "0";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(0, getCatalogEntry().getInteger());
}

TEST_F(ParserTest, parse_Integer_Max)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER;
  line[col].raw = "4294967295";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(4294967295, getCatalogEntry().getInteger());
}

TEST_F(ParserTest, parse_Integer_Invalid)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER;
  line[col].raw = "INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Integer_Invalid_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER;
  line[col].raw = "INVALID";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(0, getCatalogEntry().getInteger());
}

TEST_F(ParserTest, parse_Integer_Invalid_Negative)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER;
  line[col].raw = "-1";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Integer_Invalid_Negative_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER;
  line[col].raw = "-1";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(0, getCatalogEntry().getInteger());
}

TEST_F(ParserTest, parse_Integer_Empty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER;
  line[col].raw = "";
  stringsToStream(line);

  tryToParseStream(0, true);
}

}

namespace typeindex
{

TEST_F(ParserTest, parse_Index)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INDEX;
  line[col].raw = "NAME_LIST_LAST";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(1, getCatalogEntry().getIndex());
}

TEST_F(ParserTest, parse_Index_Invalid)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INDEX;
  line[col].raw = "INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Index_Invalid_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INDEX;
  line[col].raw = "INVALID";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
  ASSERT_EQ(-1, getCatalogEntry().getIndex());
}

TEST_F(ParserTest, parse_Index_Empty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INDEX;
  line[col].raw = "";
  stringsToStream(line);

  tryToParseStream(0, true);
}

}

namespace typeintegerrange
{

TEST_F(ParserTest, parse_IntegerRange_Min)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER_RANGE;
  line[col].raw = "0-1";
  stringsToStream(line);

  tryToParseStream();
  const grb::type::IntegerRange& range = getCatalogEntry().getIntegerRange();
  ASSERT_EQ(2, range.size());
  ASSERT_EQ(0, range[0]);
  ASSERT_EQ(1, range[1]);
}

TEST_F(ParserTest, parse_IntegerRange_Max)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER_RANGE;
  line[col].raw = "4294967294-4294967295";
  stringsToStream(line);

  tryToParseStream();
  const grb::type::IntegerRange& range = getCatalogEntry().getIntegerRange();
  ASSERT_EQ(2, range.size());
  ASSERT_EQ(4294967294, range[0]);
  ASSERT_EQ(4294967295, range[1]);
}

TEST_F(ParserTest, parse_IntegerRange_Invalid)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER_RANGE;
  line[col].raw = "INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_IntegerRange_Invalid_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER_RANGE;
  line[col].raw = "INVALID";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
  const grb::type::IntegerRange& range = getCatalogEntry().getIntegerRange();
  ASSERT_EQ(0, range.size());
}

TEST_F(ParserTest, parse_IntegerRange_OneNumber)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER_RANGE;
  line[col].raw = "0";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_IntegerRange_OneNumber_Negative)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER_RANGE;
  line[col].raw = "-1";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_IntegerRange_TwoNumber_Negative)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER_RANGE;
  line[col].raw = "-1--2";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_IntegerRange_ThreeNumber)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INTEGER_RANGE;
  line[col].raw = "0-1-2";
  stringsToStream(line);

  tryToParseStream(0, true);
}

}

namespace typeindexlist
{

TEST_F(ParserTest, parse_IndexList)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INDEX_LIST;
  line[col].raw = "NAME_LIST_FIRST,NAME_LIST_LAST,NAME_LIST_LAST,NAME_LIST_FIRST";
  stringsToStream(line);

  tryToParseStream();
  const grb::type::IndexList& list = getCatalogEntry().getIndexList();
  ASSERT_EQ(4, list.size());
  ASSERT_EQ(0, list[0]);
  ASSERT_EQ(1, list[1]);
  ASSERT_EQ(1, list[2]);
  ASSERT_EQ(0, list[3]);
}

TEST_F(ParserTest, parse_IndexList_Invalid)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INDEX_LIST;
  line[col].raw = "INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_IndexList_Invalid_Last)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INDEX_LIST;
  line[col].raw = "NAME_LIST_FIRST,NAME_LIST_LAST,NAME_LIST_LAST,INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}


TEST_F(ParserTest, parse_IndexList_Invalid_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INDEX_LIST;
  line[col].raw = "INVALID";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
  const grb::type::IndexList& list = getCatalogEntry().getIndexList();
  ASSERT_EQ(0, list.size());
}

TEST_F(ParserTest, parse_IndexList_Empty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::INDEX_LIST;
  line[col].raw = "";
  stringsToStream(line);

  tryToParseStream(0, true);
}

}

namespace typefloat
{

TEST_F(ParserTest, parse_Float_Min)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLOAT;
  line[col].raw = "-9876543210.0123456789";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_FLOAT_EQ(-9876543210.0123456789, getCatalogEntry().getFloat());
}

TEST_F(ParserTest, parse_Float_Zero)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLOAT;
  line[col].raw = "0.0";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_FLOAT_EQ(0.0, getCatalogEntry().getFloat());
}

TEST_F(ParserTest, parse_Float_Max)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLOAT;
  line[col].raw = "9876543210.0123456789";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_FLOAT_EQ(9876543210.0123456789, getCatalogEntry().getFloat());
}

TEST_F(ParserTest, parse_Float_Invalid)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLOAT;
  line[col].raw = "INVALID";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_Float_Invalid_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLOAT;
  line[col].raw = "INVALID";
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
  ASSERT_FLOAT_EQ(0.0, getCatalogEntry().getFloat());
}

TEST_F(ParserTest, parse_Float_Empty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::FLOAT;
  line[col].raw = "";
  stringsToStream(line);

  tryToParseStream(0, true);
}

}

namespace typestring
{

TEST_F(ParserTest, parse_String)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::STRING;
  line[col].raw = "JUST A STRING";
  stringsToStream(line);

  tryToParseStream();
  ASSERT_STREQ("JUST A STRING",  getCatalogEntry().getString().c_str());
}

TEST_F(ParserTest, parse_String_Empty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::STRING;
  line[col].raw.clear();
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_String_Empty_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::STRING;
  line[col].raw.clear();
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
  ASSERT_STREQ("",  getCatalogEntry().getString().c_str());
}

}

namespace typestringlist
{

TEST_F(ParserTest, parse_StringList_One)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::STRING_LIST;
  line[col].raw = "JUST A STRING";
  stringsToStream(line);

  tryToParseStream();
  const grb::type::StringList& list =  getCatalogEntry().getStringList();
  ASSERT_EQ(1, list.size());
  ASSERT_STREQ("JUST A STRING", list[0].c_str());
}

TEST_F(ParserTest, parse_StringList_Two)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::STRING_LIST;
  line[col].raw = "One,Two";
  stringsToStream(line);

  tryToParseStream();
  const grb::type::StringList& list =  getCatalogEntry().getStringList();
  ASSERT_EQ(2, list.size());
  ASSERT_STREQ("One", list[0].c_str());
  ASSERT_STREQ("Two", list[1].c_str());
}

TEST_F(ParserTest, parse_StringList_Two_FirstEmpty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::STRING_LIST;
  line[col].raw = ",Two";
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_StringList_Two_SecondEmpty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::STRING_LIST;
  line[col].raw = "One,";
  stringsToStream(line);

  tryToParseStream();
  const grb::type::StringList& list =  getCatalogEntry().getStringList();
  ASSERT_EQ(1, list.size());
  ASSERT_STREQ("One", list[0].c_str());
}

TEST_F(ParserTest, parse_StringList_Two_BothEmpty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::STRING_LIST;
  line[col].raw = ",";
  stringsToStream(line);

  tryToParseStream(0, true);
}


TEST_F(ParserTest, parse_StringList_Empty)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::STRING_LIST;
  line[col].raw.clear();
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_StringList_Empty_Optional)
{
  TypeValueVector line = DEFAULT_ROW;
  std::size_t col = grb::type::STRING_LIST;
  line[col].raw.clear();
  line[col].required = false;
  stringsToStream(line);

  tryToParseStream();
  const grb::type::StringList& list =  getCatalogEntry().getStringList();
  ASSERT_EQ(0, list.size());
}

}

} // namespace testing
