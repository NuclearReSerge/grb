#include "Tools/ParserDatabase.h"

#include "test/Mock/CatalogMock.h"
#include "test/Mock/CatalogEntryMock.h"
#include "test/Mock/DataBaseFormatMock.h"
#include "test/Mock/MockHelper.h"
#include "test/Mock/NameMapperMock.h"

#include <gtest/gtest.h>

namespace
{

struct ColumnDef
{
  ColumnDef(grb::type::ValueType valueType = grb::type::UNDEFINED_VALUE,
            bool isRequired = false,
            grb::type::UnitType unitType = grb::type::UNDEFINED_UNIT)
    : _unitType(unitType), _valueType(valueType), _isRequired(isRequired)
  {}

  grb::type::UnitType _unitType;
  grb::type::ValueType _valueType;
  bool _isRequired = false;
};

const std::vector<std::string> INDEX_LIST
{
  "index0",
  "index1",
  "index2",
  "index3"
};

}

namespace grb
{

class CatalogEntryDummy
{
public:
  grb::type::Flag* getFlag(grb::type::ColumnType) { return &_flag; }
  grb::type::Integer* getInteger(grb::type::ColumnType) { return &_integer; }
  grb::type::Index* getIndex(grb::type::ColumnType) { return &_index; }
  grb::type::IntegerRange* getIntegerRange(grb::type::ColumnType)
  {
    _integerRange.clear();
    return &_integerRange;
  }
  grb::type::IndexList* getIndexList(grb::type::ColumnType)
  {
    _indexList.clear();
    return &_indexList;
  }
  grb::type::Float* getFloat(grb::type::ColumnType) { return &_float; }
  grb::type::String* getString(grb::type::ColumnType) { return &_string; }
  grb::type::StringList* getStringList(grb::type::ColumnType)
  {
    _stringList.clear();
    return &_stringList;
  }

  grb::type::String* getStringException(grb::type::ColumnType)
  {
    grb::Exception exc(type::EXCEPTION_CRITICAL, "Throw Critical Exception", PRETTY_FUNCTION);
    throw exc;
  }

  grb::type::Flag _flag;
  grb::type::Integer _integer;
  grb::type::Index _index;
  grb::type::IntegerRange _integerRange;
  grb::type::IndexList _indexList;
  grb::type::Float _float;
  grb::type::String _string;
  grb::type::StringList _stringList;
};

} //namespace


namespace testing
{

class ParserDatabaseTest : public Test
{
protected:
  void SetUp()
  {
    _stream = new std::stringstream;
    _catalog = new grb::CatalogMock(grb::type::UNDEFINED_CATALOG);
  }

  void TearDown()
  {
    delete _stream;
    delete _catalog;
    delete _format;
    delete _parser;
    delete _mapper;
  }

  void tryToConstructFile(const std::string& filename)
  {
    try
    {
      _parser = new grb::ParserDatabase(filename, *_format, *_catalog);
    }
    catch (const grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  void tryToConstructStream()
  {
    try
    {
      _parser = new grb::ParserDatabase(_stream, *_format, *_catalog);
    }
    catch (const grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  void tryToParse()
  {
    try
    {
      _parser = new grb::ParserDatabase(_stream, *_format, *_catalog);
      _result = _parser->parse();
      _rows = _parser->getNumberOfRows();
    }
    catch (const grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  void setupFormat()
  {
    int i = 0;
    _format = new grb::DataBaseFormatMock(grb::type::UNDEFINED_DATABASE_FORMAT);

    for (const ColumnDef& def : _columnDefs)
    {
      _format->getDataTypes().push_back(new grb::DataBaseColumn(
            (grb::type::ColumnType) i++, def._unitType, def._valueType, def._isRequired));
    }
    _format->setColumnFlags();
  }

  void setupCatalogEntry(bool valid = true)
  {
    _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);

    EXPECT_CALL(*_catalog, createEntry())
        .WillRepeatedly(Return(_entry));
    EXPECT_CALL(*_entry, isValid())
        .WillRepeatedly(Return(valid));
  }

  void cleanCatalogEntry()
  {
    _catalog->getEntries().clear();
    if (!_thrown)
      delete _entry;
  }

  void setupFlag(int noOfCalls)
  {
    EXPECT_CALL(*_entry, getFlag(_))
        .Times(noOfCalls)
        .WillRepeatedly(Invoke(&_dummy, &grb::CatalogEntryDummy::getFlag));
  }
  void setupInteger(int noOfCalls)
  {
    EXPECT_CALL(*_entry, getInteger(_))
        .Times(noOfCalls)
        .WillRepeatedly(Invoke(&_dummy, &grb::CatalogEntryDummy::getInteger));
  }
  void setupIndex(int noOfCalls)
  {
    _mapper = new grb::mapper::NameMapperMock(grb::type::UNDEFINED_COLUMN);
    EXPECT_CALL(*_mapper, getList())
        .WillOnce(ReturnRef(INDEX_LIST));
    _mapper->initiateMock();

    EXPECT_CALL(*_entry, getIndex(_))
        .Times(noOfCalls)
        .WillRepeatedly(Invoke(&_dummy, &grb::CatalogEntryDummy::getIndex));
    EXPECT_CALL(*_entry, getMapper(_))
        .Times(noOfCalls)
        .WillRepeatedly(Return(_mapper));
  }
  void setupIntegerRange(int noOfCalls)
  {
    EXPECT_CALL(*_entry, getIntegerRange(_))
        .Times(noOfCalls)
        .WillRepeatedly(Invoke(&_dummy, &grb::CatalogEntryDummy::getIntegerRange));
  }
  void setupIndexList(int noOfCalls)
  {
    _mapper = new grb::mapper::NameMapperMock(grb::type::UNDEFINED_COLUMN);
    EXPECT_CALL(*_mapper, getList())
        .WillOnce(ReturnRef(INDEX_LIST));
    _mapper->initiateMock();

    EXPECT_CALL(*_entry, getIndexList(_))
        .Times(noOfCalls)
        .WillRepeatedly(Invoke(&_dummy, &grb::CatalogEntryDummy::getIndexList));
    EXPECT_CALL(*_entry, getMapper(_))
        .Times(noOfCalls)
        .WillRepeatedly(Return(_mapper));
  }
  void setupFloat(int noOfCalls)
  {
    EXPECT_CALL(*_entry, getFloat(_))
        .Times(noOfCalls)
        .WillRepeatedly(Invoke(&_dummy, &grb::CatalogEntryDummy::getFloat));
  }
  void setupString(int noOfCalls)
  {
    EXPECT_CALL(*_entry, getString(_))
        .Times(noOfCalls)
        .WillRepeatedly(Invoke(&_dummy, &grb::CatalogEntryDummy::getString));
  }
  void setupStringList(int noOfCalls)
  {
    EXPECT_CALL(*_entry, getStringList(_))
        .Times(noOfCalls)
        .WillRepeatedly(Invoke(&_dummy, &grb::CatalogEntryDummy::getStringList));
  }
  bool _result = false;
  bool _thrown = false;
  std::size_t _rows = 0;
  std::stringstream* _stream = nullptr;
  grb::Parser* _parser = nullptr;
  grb::DataBaseFormatMock* _format = nullptr;
  grb::CatalogMock* _catalog = nullptr;
  grb::CatalogEntryMock* _entry = nullptr;
  grb::mapper::NameMapperMock* _mapper = nullptr;
  grb::CatalogEntryDummy _dummy;
  std::vector<ColumnDef> _columnDefs;
};

/***************************************************************************************************
 *
 * CONSTRUCTOR
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, ConstructorFile_FileDoesNotExist)
{
  std::string filename = "unknown.file";

  tryToConstructFile(filename);

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ConstructorFile_DatabaseFormatIsEmpty)
{
  _format = new grb::DataBaseFormatMock(grb::type::UNDEFINED_DATABASE_FORMAT);

  std::string filename = __FILE__;

  tryToConstructFile(filename);

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ConstructorFile_DatabaseFormatHasUndefinedColumn)
{
  _format = new grb::DataBaseFormatMock(grb::type::UNDEFINED_DATABASE_FORMAT);
  _format->getDataTypes().push_back(new grb::DataBaseColumn(grb::type::UNDEFINED_COLUMN));

  std::string filename = __FILE__;

  tryToConstructFile(filename);

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ConstructorFile_Positive)
{
  _columnDefs =
  {
    { grb::type::UNDEFINED_VALUE, false, grb::type::UNDEFINED_UNIT }
  };
  setupFormat();

  std::string filename = __FILE__;

  tryToConstructFile(filename);

  ASSERT_NE(nullptr, _parser);
}

TEST_F(ParserDatabaseTest, ConstructorStream_StreamIsNull)
{
  delete _stream;
  _stream = nullptr;

  tryToConstructStream();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ConstructorStream_Positive)
{
  _columnDefs =
  {
    { grb::type::UNDEFINED_VALUE, false, grb::type::UNDEFINED_UNIT }
  };
  setupFormat();

  tryToConstructStream();

  ASSERT_NE(nullptr, _parser);
}

/***************************************************************************************************
 *
 * PARSE
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, Parse_EmptyStream)
{
  _columnDefs =
  {
    { grb::type::UNDEFINED_VALUE, false, grb::type::UNDEFINED_UNIT }
  };
  setupFormat();

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, Parse_EmptyLinesOnly)
{
  _columnDefs =
  {
    { grb::type::UNDEFINED_VALUE, false, grb::type::UNDEFINED_UNIT }
  };
  setupFormat();

  *_stream << "\n";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, Parse_CommentsOnly)
{
  _columnDefs =
  {
    { grb::type::UNDEFINED_VALUE, false, grb::type::UNDEFINED_UNIT }
  };
  setupFormat();

  *_stream << "# COMMENT";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, Parse_EmptyLinesAndCommentsOnly)
{
  _columnDefs =
  {
    { grb::type::UNDEFINED_VALUE, false, grb::type::UNDEFINED_UNIT }
  };
  setupFormat();

  *_stream << "\n"
              "\n"
              "# COMMENT 1\n"
              "\n"
              "# COMMENT 2\n";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, Parse_CatalogEntryIsNull)
{
  _columnDefs =
  {
    { grb::type::UNDEFINED_VALUE, false, grb::type::UNDEFINED_UNIT }
  };
  setupFormat();

  *_stream << "something";

  EXPECT_CALL(*_catalog, createEntry())
      .WillOnce(Return(nullptr));

  tryToParse();

  ASSERT_TRUE(_thrown);
}

/***************************************************************************************************
 *
 * PARSE FLAG
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, ParseFlag_CatalogEntryGetIsNull)
{
  _columnDefs =
  {
    { grb::type::FLAG, true }
  };
  setupFormat();

  _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  EXPECT_CALL(*_catalog, createEntry())
      .WillRepeatedly(Return(_entry));
  EXPECT_CALL(*_entry, getFlag(_))
      .WillOnce(Return(nullptr));

  *_stream << "A|";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseFlag_UnknownValue)
{
  _columnDefs =
  {
    { grb::type::FLAG, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupFlag(1);

  *_stream << "A|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseFlag_OneColumn_Positive)
{
  _columnDefs =
  {
    { grb::type::FLAG, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupFlag(2);

  *_stream << "N|\n"
              "Y|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}


TEST_F(ParserDatabaseTest, ParseFlag_TwoColumns_FirstRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::FLAG, true },
    { grb::type::FLAG, false }
  };
  setupFormat();
  setupCatalogEntry();
  setupFlag(4);

  *_stream << "N|Y|\n"
              "N||";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseFlag_TwoColumns_SecondRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::FLAG, false },
    { grb::type::FLAG, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupFlag(4);

  *_stream << "N|Y|\n"
              "|Y|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseFlag_TwoColumns_BothRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::FLAG, true },
    { grb::type::FLAG, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupFlag(4);

  *_stream << "N|Y|\n"
              "N|Y|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

/***************************************************************************************************
 *
 * PARSE INTEGER
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, ParseInteger_CatalogEntryGetIsNull)
{
  _columnDefs =
  {
    { grb::type::INTEGER, true }
  };
  setupFormat();

  _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  EXPECT_CALL(*_catalog, createEntry())
      .WillRepeatedly(Return(_entry));
  EXPECT_CALL(*_entry, getInteger(_))
      .WillOnce(Return(nullptr));

  *_stream << "01234567890|";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseInteger_UnknownValue)
{
  _columnDefs =
  {
    { grb::type::INTEGER, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupInteger(1);

  *_stream << "-|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseInteger_NegativeValue)
{
  _columnDefs =
  {
    { grb::type::INTEGER, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupInteger(1);

  *_stream << "-123456789|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseInteger_OneColumn_Positive)
{
  _columnDefs =
  {
    { grb::type::INTEGER, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupInteger(2);

  *_stream << "0123456789|\n"
              "9876543210|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}


TEST_F(ParserDatabaseTest, ParseInteger_TwoColumns_FirstRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INTEGER, true },
    { grb::type::INTEGER, false }
  };
  setupFormat();
  setupCatalogEntry();
  setupInteger(4);

  *_stream << "0123456789|9876543210|\n"
              "0123456789||";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseInteger_TwoColumns_SecondRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INTEGER, false },
    { grb::type::INTEGER, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupInteger(4);

  *_stream << "0123456789|9876543210|\n"
              "          |9876543210|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseInteger_TwoColumns_BothRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INTEGER, true },
    { grb::type::INTEGER, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupInteger(4);

  *_stream << "0123456789|9876543210|\n"
              "0123456789|9876543210|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

/***************************************************************************************************
 *
 * PARSE INDEX
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, ParseIndex_CatalogEntryGetMapperIsNull)
{
  _columnDefs =
  {
    { grb::type::INDEX, true }
  };
  setupFormat();

  _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  EXPECT_CALL(*_catalog, createEntry())
      .WillRepeatedly(Return(_entry));
  EXPECT_CALL(*_entry, getIndex(_))
      .WillOnce(Invoke(&_dummy, &grb::CatalogEntryDummy::getIndex));
  EXPECT_CALL(*_entry, getMapper(_))
      .WillOnce(Return(nullptr));

  *_stream << "undefined-index|";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseIndex_CatalogEntryGetIsNull)
{
  _columnDefs =
  {
    { grb::type::INDEX, true }
  };
  setupFormat();

  _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  _mapper = new grb::mapper::NameMapperMock(grb::type::UNDEFINED_COLUMN);
  EXPECT_CALL(*_catalog, createEntry())
      .WillRepeatedly(Return(_entry));
  EXPECT_CALL(*_entry, getIndex(_))
      .WillOnce(Return(nullptr));
  EXPECT_CALL(*_entry, getMapper(_))
      .WillOnce(Return(_mapper));

  *_stream << "undefined-index|";

  tryToParse();

  ASSERT_TRUE(_thrown);
}


TEST_F(ParserDatabaseTest, ParseIndex_UnknownValue)
{
  _columnDefs =
  {
    { grb::type::INDEX, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndex(1);

  *_stream << "undefined-index|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIndex_OneColumn_Positive)
{
  _columnDefs =
  {
    { grb::type::INDEX, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndex(2);

  *_stream << "index0|\n"
              "index0|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}


TEST_F(ParserDatabaseTest, ParseIndex_TwoColumns_FirstRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INDEX, true },
    { grb::type::INDEX, false }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndex(4);

  *_stream << "index0|index1|\n"
              "index0||";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIndex_TwoColumns_SecondRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INDEX, false },
    { grb::type::INDEX, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndex(4);

  *_stream << "index0|index1|\n"
              "      |index1|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIndex_TwoColumns_BothRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INDEX, true },
    { grb::type::INDEX, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndex(4);

  *_stream << "index0|index1|\n"
              "index0|index1|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

/***************************************************************************************************
 *
 * PARSE INTEGER RANGE
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, ParseIntegerRange_CatalogEntryGetIsNull)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();

  _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  EXPECT_CALL(*_catalog, createEntry())
      .WillRepeatedly(Return(_entry));
  EXPECT_CALL(*_entry, getIntegerRange(_))
      .WillOnce(Return(nullptr));

  *_stream << "12345-67890|";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseIntegerRange_SingleValue)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(1);

  *_stream << "1234567890|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}


TEST_F(ParserDatabaseTest, ParseIntegerRange_NoValues)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(1);

  *_stream << "-|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIntegerRange_NoFirstValue)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(1);

  *_stream << "-67890|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIntegerRange_NoSecondValue)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(1);

  *_stream << "12345-|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIntegerRange_FirstNegativeValue)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(1);

  *_stream << "-12345-67890|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIntegerRange_SecondNegativeValue)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(1);

  *_stream << "12345--67890|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIntegerRange_MoreThanTwo)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(1);

  *_stream << "123-456-7890|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}


TEST_F(ParserDatabaseTest, ParseIntegerRange_OneColumn_Positive)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(2);

  *_stream << "01234-56789|\n"
              "98765-43210|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIntegerRange_TwoColumns_FirstRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true },
    { grb::type::INTEGER_RANGE, false }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(4);

  *_stream << "01234-56789|98765-43210|\n"
              "01234-56789||";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIntegerRange_TwoColumns_SecondRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, false },
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(4);

  *_stream << "01234-56789|98765-43210|\n"
              "           |98765-43210|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIntegerRange_TwoColumns_BothRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INTEGER_RANGE, true },
    { grb::type::INTEGER_RANGE, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIntegerRange(4);

  *_stream << "01234-56789|98765-43210|\n"
              "01234-56789|98765-43210|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

/***************************************************************************************************
 *
 * PARSE INDEX LIST
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, ParseIndexList_CatalogEntryGetMapperIsNull)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, true }
  };
  setupFormat();

  _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  EXPECT_CALL(*_catalog, createEntry())
      .WillRepeatedly(Return(_entry));
  EXPECT_CALL(*_entry, getIndexList(_))
      .WillOnce(Invoke(&_dummy, &grb::CatalogEntryDummy::getIndexList));
  EXPECT_CALL(*_entry, getMapper(_))
      .WillOnce(Return(nullptr));

  *_stream << "index0,index1|";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseIndexList_CatalogEntryGetIsNull)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, true }
  };
  setupFormat();

  _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  _mapper = new grb::mapper::NameMapperMock(grb::type::UNDEFINED_COLUMN);
  EXPECT_CALL(*_catalog, createEntry())
      .WillRepeatedly(Return(_entry));
  EXPECT_CALL(*_entry, getIndexList(_))
      .WillOnce(Return(nullptr));
  EXPECT_CALL(*_entry, getMapper(_))
      .WillOnce(Return(_mapper));

  *_stream << "index0,index1|";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseIndexList_EmptyValues)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndexList(1);

  *_stream << ",|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIndexList_EmptyFirstValue)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndexList(1);

  *_stream << ",index1|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIndexList_EmptySecondValue)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndexList(1);

  *_stream << "index0,,|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}


TEST_F(ParserDatabaseTest, ParseIndexList_UnknownFirstValue)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndexList(1);

  *_stream << "undefined-index,index1|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIndexList_UnknownSecondValue)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndexList(1);

  *_stream << "index0,undefined-index|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIndexList_OneColumn_Positive)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndexList(2);

  *_stream << "index0,index1|\n"
              "index0,index1|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIndexList_TwoColumns_FirstRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, true },
    { grb::type::INDEX_LIST, false }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndexList(4);

  *_stream << "index0,index1|index2,index3|\n"
              "index0,index1|             |";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIndexList_TwoColumns_SecondRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, false },
    { grb::type::INDEX_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndexList(4);

  *_stream << "index0,index1|index2,index3|\n"
              "             |index2,index3|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseIndexList_TwoColumns_BothRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::INDEX_LIST, true },
    { grb::type::INDEX_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupIndexList(4);

  *_stream << "index0,index1|index2,index3|\n"
              "index0,index1|index2,index3|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

/***************************************************************************************************
 *
 * PARSE FLOAT
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, ParseFloat_CatalogEntryGetIsNull)
{
  _columnDefs =
  {
    { grb::type::FLOAT, true }
  };
  setupFormat();

  _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  EXPECT_CALL(*_catalog, createEntry())
      .WillRepeatedly(Return(_entry));
  EXPECT_CALL(*_entry, getFloat(_))
      .WillOnce(Return(nullptr));

  *_stream << "0.1234567890|";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseFloat_UnknownValue)
{
  _columnDefs =
  {
    { grb::type::FLOAT, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupFloat(1);

  *_stream << "-|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseFloat_OneColumn_Positive)
{
  _columnDefs =
  {
    { grb::type::FLOAT, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupFloat(2);

  *_stream << " 0.123456789|\n"
              "-9.876543210|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseFloat_TwoColumns_FirstRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::FLOAT, true },
    { grb::type::FLOAT, false }
  };
  setupFormat();
  setupCatalogEntry();
  setupFloat(4);

  *_stream << "0.123456789|9.876543210|\n"
              "0.123456789||";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseFloat_TwoColumns_SecondRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::FLOAT, false },
    { grb::type::FLOAT, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupFloat(4);

  *_stream << "0.123456789|9.876543210|\n"
              "           |9.876543210|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseFloat_TwoColumns_BothRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::FLOAT, true },
    { grb::type::FLOAT, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupFloat(4);

  *_stream << "0.123456789|9.876543210|\n"
              "0.123456789|9.876543210|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

/***************************************************************************************************
 *
 * PARSE STRING
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, ParseString_CatalogEntryGetIsNull)
{
  _columnDefs =
  {
    { grb::type::STRING, true }
  };
  setupFormat();

  _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  EXPECT_CALL(*_catalog, createEntry())
      .WillRepeatedly(Return(_entry));
  EXPECT_CALL(*_entry, getString(_))
      .WillOnce(Return(nullptr));

  *_stream << "string1|";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseString_OneColumn_Positive)
{
  _columnDefs =
  {
    { grb::type::STRING, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupString(2);

  *_stream << "string1|\n"
              "string1|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseString_TwoColumns_FirstRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::STRING, true },
    { grb::type::STRING, false }
  };
  setupFormat();
  setupCatalogEntry();
  setupString(4);

  *_stream << "string1|string2|\n"
              "string1|       |";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseString_TwoColumns_SecondRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::STRING, false },
    { grb::type::STRING, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupString(4);

  *_stream << "string1|string2|\n"
              "       |string2|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseString_TwoColumns_BothRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::STRING, true },
    { grb::type::STRING, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupString(4);

  *_stream << "string1|string2|\n"
              "string1|string2|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

/***************************************************************************************************
 *
 * PARSE STRING LIST
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, ParseStringList_CatalogEntryGetIsNull)
{
  _columnDefs =
  {
    { grb::type::STRING_LIST, true }
  };
  setupFormat();

  _entry = new grb::CatalogEntryMock(grb::type::UNDEFINED_CATALOG);
  EXPECT_CALL(*_catalog, createEntry())
      .WillRepeatedly(Return(_entry));
  EXPECT_CALL(*_entry, getStringList(_))
      .WillOnce(Return(nullptr));

  *_stream << "string1,string2|";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseStringList_OneEmpty)
{
  _columnDefs =
  {
    { grb::type::STRING_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupStringList(1);

  *_stream << "       |";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseStringList_TwoEmpty)
{
  _columnDefs =
  {
    { grb::type::STRING_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupStringList(1);

  *_stream << "   ,    |";

  tryToParse();

  ASSERT_TRUE(_thrown);
}

TEST_F(ParserDatabaseTest, ParseStringList_OneColumn_Positive)
{
  _columnDefs =
  {
    { grb::type::STRING_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupStringList(2);

  *_stream << "string1,string2|\n"
              "string1,string2|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseStringList_TwoColumns_FirstRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::STRING_LIST, true },
    { grb::type::STRING_LIST, false }
  };
  setupFormat();
  setupCatalogEntry();
  setupStringList(4);

  *_stream << "string1,string2|string3,string4|\n"
              "string1,string2|               |";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseStringList_TwoColumns_SecondRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::STRING_LIST, false },
    { grb::type::STRING_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupStringList(4);

  *_stream << "string1,string2|string3,string4|\n"
              "               |string3,string4|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, ParseStringList_TwoColumns_BothRequred_Positive)
{
  _columnDefs =
  {
    { grb::type::STRING_LIST, true },
    { grb::type::STRING_LIST, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupStringList(4);

  *_stream << "string1,string2|string3,string4|\n"
              "string1,string2|string3,string4|";

  tryToParse();

  ASSERT_TRUE(_result);
  ASSERT_EQ(2, _parser->getNumberOfRows());
  cleanCatalogEntry();
}

/***************************************************************************************************
 *
 *
 *
 **************************************************************************************************/
TEST_F(ParserDatabaseTest, Parse_LessDataThanExpected)
{
  _columnDefs =
  {
    { grb::type::STRING, true },
    { grb::type::STRING, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupString(3);

  *_stream << "string1|string2|\n"
              "string1|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, Parse_MoreDataThanExpected)
{
  _columnDefs =
  {
    { grb::type::STRING, true },
    { grb::type::STRING, true }
  };
  setupFormat();
  setupCatalogEntry();
  setupString(4);

  *_stream << "string1|string2|\n"
              "string1|string2|string3|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, Parse_CatalogEntryNotValid)
{
  _columnDefs =
  {
    { grb::type::STRING, true },
    { grb::type::STRING, true }
  };
  setupFormat();
  setupCatalogEntry(false);
  setupString(2);

  *_stream << "string1|string2|\n"
              "string1|string2|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}

TEST_F(ParserDatabaseTest, Parse_UnsupportedValue)
{
  _columnDefs =
  {
    { grb::type::STRING, true },
    { grb::type::UNDEFINED_VALUE, true }
  };
  setupFormat();
  setupCatalogEntry(false);
  setupString(1);

  *_stream << "string1|string2|\n"
              "string1|string2|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}


TEST_F(ParserDatabaseTest, Parse_CriticalException)
{
  _columnDefs =
  {
    { grb::type::STRING, true },
    { grb::type::STRING, true }
  };
  setupFormat();
  setupCatalogEntry(false);
  EXPECT_CALL(*_entry, getString(_))
      .Times(1)
      .WillRepeatedly(Invoke(&_dummy, &grb::CatalogEntryDummy::getStringException));

  *_stream << "string1|string2|\n"
              "string1|string2|";

  tryToParse();

  ASSERT_TRUE(_thrown);
  cleanCatalogEntry();
}


} // namespace testing
