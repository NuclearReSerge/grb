#include "Tools/Parser.h"
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
const VecStr DEFAULT_ROW_REQUIRED
{
  "GRB 600101",
  "1960-01-01 00:00:00.0",
  "APEX",
  "", "", "-1",
  "",
  "N", "N",
  "0", "0",
  "",
  "BAT trigger",
  "1974ApJ...188L...1S",
  "", "", "", "", "", "",
  "", "", "", "", "", "",
  "", "",
  "",
  ""
};
const VecStr DEFAULT_ROW_ALL_VALUES
{
  "GRB 600101",
  "1960-01-01 00:00:00.0",
  "APEX",
  "", "", "-1",
  "",
  "N", "N",
  "0", "0",
  "",
  "BAT trigger",
  "1974ApJ...188L...1S",
  "", "", "", "", "", "",
  "", "", "", "", "", "",
  "", "",
  "",
  ""
};
}

class ParserTest : public Test
{
protected:
  void SetUp()
  {
    _parser = nullptr;
    _catalog = new Catalog;
    _stream = new std::stringstream;

  }

  void TearDown()
  {
    delete _stream;
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
      _parser = new Parser(filename);
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
      _parser = new Parser(_stream);
      linesParsed = _parser->parse(DataBaseFormats::instance()->getFormat(type::HEASARC_GRBCAT),
                                   *_catalog);
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
  VecStr line = DEFAULT_ROW_REQUIRED;
  for (auto& str : line)
    str.clear();
  stringsToStream(line);

  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DelimitersWhitespaceOnly)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  for (auto& str : line)
    str = "  ";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DelimitersWhitespaceAndHashOnly)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  for (auto& str : line)
    str = " # ";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  stringsToStream(line);
  tryToParseStream();
}

TEST_F(ParserTest, parse_DefaultRow_InvalidName)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::NAME].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidTime)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::TIME].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidObservatory_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::OBSERVATORY].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidObservatory_Mapper)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::OBSERVATORY] = "UNKNOWN";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordH_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::COORD_H].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordH_NotReal)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::COORD_H] = "FF";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordV_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::COORD_V].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordV_NotReal)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::COORD_V] = "FF";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordFlag_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::COORD_FLAG].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidCoordFlag_NotReal)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::COORD_FLAG] = "FF";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidRegion_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::REGION].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidRegion_Mapper)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::REGION] = "UNKNOWN";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidAfterglowFlag_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::AFTERGLOW_FLAG].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidAfterglowFlag_NotYN)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::AFTERGLOW_FLAG] = "T";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidFluxFlag_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::FLUX_FLAG].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidFluxFlag_NotYN)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::FLUX_FLAG] = "T";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidId_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::ID].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidId_NotInteger)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::ID] = "FF";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidRecordNumber_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::RECORD_NUMBER].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidRecordNumber_NotInteger)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::RECORD_NUMBER] = "FF";
  stringsToStream(line);
  tryToParseStream(0, true);
}

// ALT_NAMES skipped

TEST_F(ParserTest, parse_DefaultRow_InvalidTimeDef_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::TIME_DEF].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidTimeDef_Mapper)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::TIME_DEF] = "UNKNOWN";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidReference_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::REFERENCE].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidReference_Mapper)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::REFERENCE] = "UNKNOWN";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidReferenceList_SecondMapper)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::REFERENCE] = "1974ApJ...188L...1S,UNKNOWN";
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidT50Mod_Empty)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::T50_MOD].clear();
  stringsToStream(line);
  tryToParseStream(0, true);
}

TEST_F(ParserTest, parse_DefaultRow_InvalidT50Mod_Mapper)
{
  VecStr line = DEFAULT_ROW_REQUIRED;
  line[type::T50_MOD] = "!";
  stringsToStream(line);
  tryToParseStream(0, true);
}


TEST_F(ParserTest, parse_real_valid_entry)
{
  VecStr line
  {
    "GRB 930309A",
    "1993-03-09 03:07:49.8",
    "COMPTEL-CGRO",
    "94.8903", "-1.4087", "0.2"
    ,"irregular",
    "N", "N",
    "1528", "2759",
    "PB930309",
    "Earth Crossing Time",
    "1998ApJ...492..246K",
    "#", "#", "#", "#", "#", "#",
    "#", "#", "#", "#", "#", "#",
    "#", "#",
    "#",
    "Circular error region is approximation of irregular COMPTEL error region "
  };
  stringsToStream(line);
  tryToParseStream();
}


} // namespace test
} // namespace grb
