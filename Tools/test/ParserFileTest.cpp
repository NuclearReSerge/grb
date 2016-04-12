#include "Tools/Parser.h"

#include "Data/Catalog.h"
#include "Data/CatalogEntryGrbcat.h"
#include "Data/DataBaseFormatFactory.h"
#include "Data/DataBaseFormatGrbcat.h"
#include "Data/Observatory.h"
#include "Data/Reference.h"
#include "Data/Region.h"
#include "Data/TimeDef.h"
#include "Data/TimeMod.h"


#include <gtest/gtest.h>
#include <sstream>

using namespace ::testing;

namespace grb
{
namespace test
{

class ParserFileTest : public Test
{
protected:
  void SetUp()
  {
    _parser = nullptr;
  }

  void TearDown()
  {
    delete _parser;
  }

  Parser* _parser;
};

void checkRecordGRBCAT_1(const CatalogEntryGRBCAT& entry)
{
  ASSERT_EQ(1, entry.getRecordNumber());
  ASSERT_EQ(1, entry.getId());
  ASSERT_STREQ("GRB 670702", entry.getName().c_str());
  ASSERT_EQ(0, entry.getAltNames().size());
  ASSERT_FLOAT_EQ(39673.596851851798, entry.getTime().getTime());
  ASSERT_STREQ("Earth Crossing Time", TimeDef::instance()->getName(entry.getTimeDef()).c_str());
  ASSERT_STREQ("VELA", Observatory::instance()->getName(entry.getObservatory()).c_str());
  ASSERT_FLOAT_EQ(0.0, entry.getCoodinates().getHorizontal());
  ASSERT_FLOAT_EQ(0.0, entry.getCoodinates().getVertical());
  ASSERT_FLOAT_EQ(-1.0, entry.getCoodinates().getCoordFlag());
  ASSERT_EQ(-1, entry.getRegion());
  ASSERT_EQ(false, entry.getAfterglowFlag());
  ASSERT_EQ(1, entry.getReference().size());
  ASSERT_STREQ("1974ApJ...188L...1S", Reference::instance()->getName(entry.getReference()[0]).c_str());
  ASSERT_EQ(-1, entry.getT50().getMod());
  ASSERT_FLOAT_EQ(0.0, entry.getT50().getDuration());
  ASSERT_FLOAT_EQ(0.0, entry.getT50().getError());
  ASSERT_EQ(0, entry.getT50().getRange().size());
  ASSERT_EQ(0, entry.getT50().getEmin());
  ASSERT_EQ(0, entry.getT50().getEmax());
  ASSERT_EQ(-1, entry.getT90().getMod());
  ASSERT_FLOAT_EQ(0.0, entry.getT90().getDuration());
  ASSERT_FLOAT_EQ(0.0, entry.getT90().getError());
  ASSERT_EQ(0, entry.getT90().getRange().size());
  ASSERT_EQ(0, entry.getT90().getEmin());
  ASSERT_EQ(0, entry.getT90().getEmax());
  ASSERT_FLOAT_EQ(0.0, entry.getTOther().getDuration());
  ASSERT_EQ(false, entry.getFluxFlag());
  ASSERT_EQ(true, entry.getTOther().getNotes().empty());
  ASSERT_EQ(true, entry.getFluxNotes().empty());
  ASSERT_EQ(true, entry.getLocalNotes().empty());
  ASSERT_EQ(1710, entry.getClassId());
}

void checkRecordGRBCAT_10119(const CatalogEntryGRBCAT& entry)
{
  ASSERT_EQ(10119, entry.getRecordNumber());
  ASSERT_EQ(5831, entry.getId());
  ASSERT_STREQ("GRB 050309", entry.getName().c_str());
  ASSERT_EQ(0, entry.getAltNames().size());
  ASSERT_FLOAT_EQ(53438.030104166697, entry.getTime().getTime());
  ASSERT_STREQ("BAT trigger", TimeDef::instance()->getName(entry.getTimeDef()).c_str());
  ASSERT_STREQ("SWIFT", Observatory::instance()->getName(entry.getObservatory()).c_str());
  ASSERT_FLOAT_EQ(182.62125, entry.getCoodinates().getHorizontal());
  ASSERT_FLOAT_EQ(77.617999999999995, entry.getCoodinates().getVertical());
  ASSERT_FLOAT_EQ(0.0, entry.getCoodinates().getCoordFlag());
  ASSERT_EQ(-1, entry.getRegion());
  ASSERT_EQ(true, entry.getAfterglowFlag());
  ASSERT_EQ(1, entry.getReference().size());
  ASSERT_STREQ("2005GCN..3082....1B", Reference::instance()->getName(entry.getReference()[0]).c_str());
  ASSERT_EQ(-1, entry.getT50().getMod());
  ASSERT_FLOAT_EQ(0.0, entry.getT50().getDuration());
  ASSERT_FLOAT_EQ(0.0, entry.getT50().getError());
  ASSERT_EQ(0, entry.getT50().getRange().size());
  ASSERT_EQ(0, entry.getT50().getEmin());
  ASSERT_EQ(0, entry.getT50().getEmax());
  ASSERT_EQ(-1, entry.getT90().getMod());
  ASSERT_FLOAT_EQ(0.0, entry.getT90().getDuration());
  ASSERT_FLOAT_EQ(0.0, entry.getT90().getError());
  ASSERT_EQ(0, entry.getT90().getRange().size());
  ASSERT_EQ(0, entry.getT90().getEmin());
  ASSERT_EQ(0, entry.getT90().getEmax());
  ASSERT_FLOAT_EQ(0.0, entry.getTOther().getDuration());
  ASSERT_EQ(false, entry.getFluxFlag());
  ASSERT_EQ(true, entry.getTOther().getNotes().empty());
  ASSERT_EQ(true, entry.getFluxNotes().empty());
  ASSERT_STREQ("Position is from source 1 of XRT. See afterglow table.", entry.getLocalNotes().c_str());
  ASSERT_EQ(1710, entry.getClassId());
}

TEST_F(ParserFileTest, file_Grbcat)
{
  std::string filename = "heasarc_grbcat_test.tdat";
  Catalog catalog(type::GRBCAT);
  std::size_t rows = 0;

  try
  {
    _parser = new Parser(filename,
                         DataBaseFormatFactory::instance()->getFormat(type::HEASARC_GRBCAT),
                         catalog);
    rows = _parser->parse();
  }
  catch (Exception& exc)
  {
    std::cout << exc.what() << std::endl;
  }
  ASSERT_EQ(2, rows);
  ASSERT_EQ(2, catalog.size());
  checkRecordGRBCAT_1(static_cast<const CatalogEntryGRBCAT&>(catalog[0]));
  checkRecordGRBCAT_10119(static_cast<const CatalogEntryGRBCAT&>(catalog[1]));
}

}
}
