#include "Tools/Parser.h"
#include "test/DataBaseFormatMock.h"

#include "gtest/gtest.h"
#include <sstream>

using namespace ::testing;

namespace grb
{
namespace test
{

typedef std::vector<std::string> VecStr;

namespace
{
const VecStr DEFAULT_ROW
{
  "N",
  "9999",
  "INDEX",
  "9999-9999",
  "INDEX1,INDEX2",
  "9999.9999",
  "0.0", // Julian
  "0.0",
  "STRING",
  "STRING1,STRING2"
};
}

class ParserTest : public Test
{
protected:
  void SetUp()
  {
    _parser = nullptr;
    _catalog = new Catalog;
    _format = new DataBaseFormatMock;
    _stream = new std::stringstream;

  }

  void TearDown()
  {
    delete _stream;
    delete _format;
    delete _catalog;
    delete _parser;
  }

  void stringsToStream(VecStr& vs)
  {
    bool firstCol = true;
    for(const std::string& st : vs)
    {
      if (firstCol)
        firstCol = false;
      else
        *_stream << "|";
      *_stream << st;
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
  VecStr line = DEFAULT_ROW;
  for (auto& str : line)
    str.clear();
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DelimitersWhitespaceOnly)
{
  VecStr line = DEFAULT_ROW;
  for (auto& str : line)
    str = "  ";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DelimitersWhitespaceAndHashOnly)
{
  VecStr line = DEFAULT_ROW;
  for (auto& str : line)
    str = " # ";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow)
{
  VecStr line = DEFAULT_ROW;
  stringsToStream(line);
  tryToParseStream();
}

TEST_F(ParserTest, parse_DefaultRow_InvalidName)
{
  VecStr line = DEFAULT_ROW;
  line[type::NAME].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidTime)
{
  VecStr line = DEFAULT_ROW;
  line[type::TIME].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidObservatory_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::OBSERVATORY].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidObservatory_Mapper)
{
  VecStr line = DEFAULT_ROW;
  line[type::OBSERVATORY] = "UNKNOWN";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordH_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::COORD_H].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordH_NotReal)
{
  VecStr line = DEFAULT_ROW;
  line[type::COORD_H] = "FF";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordV_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::COORD_V].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordV_NotReal)
{
  VecStr line = DEFAULT_ROW;
  line[type::COORD_V] = "FF";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordFlag_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::COORD_FLAG].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordFlag_NotReal)
{
  VecStr line = DEFAULT_ROW;
  line[type::COORD_FLAG] = "FF";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidRegion_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::REGION].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidRegion_Mapper)
{
  VecStr line = DEFAULT_ROW;
  line[type::REGION] = "UNKNOWN";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidAfterglowFlag_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::AFTERGLOW_FLAG].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidAfterglowFlag_NotYN)
{
  VecStr line = DEFAULT_ROW;
  line[type::AFTERGLOW_FLAG] = "T";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidFluxFlag_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::FLUX_FLAG].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidFluxFlag_NotYN)
{
  VecStr line = DEFAULT_ROW;
  line[type::FLUX_FLAG] = "T";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidId_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::ID].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidId_NotInteger)
{
  VecStr line = DEFAULT_ROW;
  line[type::ID] = "FF";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidRecordNumber_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::RECORD_NUMBER].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidRecordNumber_NotInteger)
{
  VecStr line = DEFAULT_ROW;
  line[type::RECORD_NUMBER] = "FF";
  stringsToStream(line);
  tryToParseStream(0, true);
}

// ALT_NAMES skipped

TEST_F(ParserTest, parse_DefaultRow_InvalidTimeDef_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::TIME_DEF].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidTimeDef_Mapper)
{
  VecStr line = DEFAULT_ROW;
  line[type::TIME_DEF] = "UNKNOWN";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidReference_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::REFERENCE].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidReference_Mapper)
{
  VecStr line = DEFAULT_ROW;
  line[type::REFERENCE] = "UNKNOWN";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidReferenceList_SecondMapper)
{
  VecStr line = DEFAULT_ROW;
  line[type::REFERENCE] = "1974ApJ...188L...1S,UNKNOWN";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidT50Mod_Empty)
{
  VecStr line = DEFAULT_ROW;
  line[type::T50_MOD].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidT50Mod_Mapper)
{
  VecStr line = DEFAULT_ROW;
  line[type::T50_MOD] = "!";
  stringsToStream(line);
  tryToParseStream(0, true);
}


TEST_F(ParserTest, parse_real_valid_entry)
{
  VecStr line
  {
    "10119", "5831",
    "GRB 050309", "",
    "53438.030104166697", "BAT trigger",
    "SWIFT",
    "182.62125", "77.617999999999995", "0", "",
    "Y",
    "2005GCN..3082....1B"
    "", "", "", "", "", "", // t50_mod, t50, t50_error, t50_range, t50_emin, t50_emax
    "", "", "", "", "", "", // t90_mod, t90, t90_error, t90_range, t90_emin, t90_emax
    "", "N", "", "" // t_other, flux_flag, notes, flux_notes
    "Position is from source 1 of XRT. See afterglow table." // local_notes
    "1710", //class
    "" // DUMMY
  };
  stringsToStream(line);
  tryToParseStream();
}


} // namespace test
} // namespace grb
