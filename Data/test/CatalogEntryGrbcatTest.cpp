#include "Data/CatalogEntryGrbcat.h"
#include "Tools/NameMapper.h"

#include <gmock/gmock.h>


namespace grb
{

class CatalogEntryGrbcatStub : public CatalogEntryGrbcat
{
public:
  type::Flag* getFlag(type::ColumnType column) { return CatalogEntryGrbcat::getFlag(column); }
  type::Integer* getInteger(type::ColumnType column) { return CatalogEntryGrbcat::getInteger(column); }
  type::Index* getIndex(type::ColumnType column) { return CatalogEntryGrbcat::getIndex(column); }
  type::IntegerRange* getIntegerRange(type::ColumnType column) { return CatalogEntryGrbcat::getIntegerRange(column); }
  type::IndexList* getIndexList(type::ColumnType column) { return CatalogEntryGrbcat::getIndexList(column); }
  type::Float* getFloat(type::ColumnType column) { return CatalogEntryGrbcat::getFloat(column); }
  type::String* getString(type::ColumnType column) { return CatalogEntryGrbcat::getString(column); }
  type::StringList* getStringList(type::ColumnType column) { return CatalogEntryGrbcat::getStringList(column); }
  mapper::NameMapper* getMapper(type::ColumnType column) { return CatalogEntryGrbcat::getMapper(column); }
  void setUnitType(type::ColumnType column, type::UnitType unitType) { CatalogEntryGrbcat::setUnitType(column, unitType); }
  bool isValid() { return CatalogEntryGrbcat::isValid(); }
};

} // namespace grb

namespace testing
{

class CatalogEntryGrbcatTest : public Test
{
protected:
  grb::CatalogEntryGrbcatStub _entryStub;
  const grb::CatalogEntryGrbcatStub& _entryConst { _entryStub };
};

TEST_F(CatalogEntryGrbcatTest, init)
{
  ASSERT_EQ(0, _entryStub.getRecordNumber());
  ASSERT_EQ(0, _entryStub.getId());
  ASSERT_TRUE(_entryStub.getName().empty());
  ASSERT_TRUE(_entryStub.getAltNames().empty());
  ASSERT_EQ(-1, _entryStub.getTimeDef());
  ASSERT_EQ(-1, _entryStub.getObservatory());
  ASSERT_DOUBLE_EQ(0.0, _entryStub.getCoordFlag());
  ASSERT_EQ(grb::type::EQUATORIAL_J2000, _entryStub.getCoodinates().getCoorType());
  ASSERT_EQ(grb::type::MODIFIED_JULIAN_DATE, _entryStub.getCoodinates().getDateType());
  ASSERT_EQ(-1, _entryStub.getRegion());
  ASSERT_FALSE(_entryStub.getAfterglowFlag());
  ASSERT_TRUE(_entryStub.getReference().empty());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT, _entryStub.getT50().getDurationUnitType());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT, _entryStub.getT50().getEnergyUnitType());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT, _entryStub.getT90().getDurationUnitType());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT, _entryStub.getT90().getEnergyUnitType());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT, _entryStub.getTOther().getDurationUnitType());
  ASSERT_FALSE(_entryStub.getFluxFlag());
  ASSERT_TRUE(_entryStub.getFluxNotes().empty());
  ASSERT_TRUE(_entryStub.getLocalNotes().empty());
  ASSERT_EQ(0, _entryStub.getClassId());
}

TEST_F(CatalogEntryGrbcatTest, initConst)
{
  ASSERT_EQ(0, _entryConst.getRecordNumber());
  ASSERT_EQ(0, _entryConst.getId());
  ASSERT_TRUE(_entryConst.getName().empty());
  ASSERT_TRUE(_entryConst.getAltNames().empty());
  ASSERT_EQ(-1, _entryConst.getTimeDef());
  ASSERT_EQ(-1, _entryConst.getObservatory());
  ASSERT_DOUBLE_EQ(0.0, _entryConst.getCoordFlag());
  ASSERT_EQ(grb::type::EQUATORIAL_J2000, _entryConst.getCoodinates().getCoorType());
  ASSERT_EQ(grb::type::MODIFIED_JULIAN_DATE, _entryConst.getCoodinates().getDateType());
  ASSERT_EQ(-1, _entryConst.getRegion());
  ASSERT_FALSE(_entryConst.getAfterglowFlag());
  ASSERT_TRUE(_entryConst.getReference().empty());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT, _entryConst.getT50().getDurationUnitType());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT, _entryConst.getT50().getEnergyUnitType());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT, _entryConst.getT90().getDurationUnitType());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT, _entryConst.getT90().getEnergyUnitType());
  ASSERT_EQ(grb::type::UNDEFINED_UNIT, _entryConst.getTOther().getDurationUnitType());
  ASSERT_FALSE(_entryConst.getFluxFlag());
  ASSERT_TRUE(_entryConst.getFluxNotes().empty());
  ASSERT_TRUE(_entryConst.getLocalNotes().empty());
  ASSERT_EQ(0, _entryConst.getClassId());
}

TEST_F(CatalogEntryGrbcatTest, getFlag)
{
  _entryStub.getAfterglowFlag() = true;
  _entryStub.getFluxFlag() = true;

  ASSERT_TRUE(*_entryStub.getFlag(grb::type::AFTERGLOW_FLAG));
  ASSERT_TRUE(*_entryStub.getFlag(grb::type::FLUX_FLAG));
  ASSERT_EQ(nullptr, _entryStub.getFlag(grb::type::UNDEFINED_COLUMN));
}

TEST_F(CatalogEntryGrbcatTest, getInteger)
{
  _entryStub.getRecordNumber() = 1;
  _entryStub.getId() = 2;
  _entryStub.getClassId() = 3;
  _entryStub.getT50().getEmin() = 4;
  _entryStub.getT50().getEmax() = 5;
  _entryStub.getT90().getEmin() = 6;
  _entryStub.getT90().getEmax() = 7;

  ASSERT_EQ(1, *_entryStub.getInteger(grb::type::RECORD_NUMBER));
  ASSERT_EQ(2, *_entryStub.getInteger(grb::type::ID));
  ASSERT_EQ(3, *_entryStub.getInteger(grb::type::CLASS));
  ASSERT_EQ(4, *_entryStub.getInteger(grb::type::T50_EMIN));
  ASSERT_EQ(5, *_entryStub.getInteger(grb::type::T50_EMAX));
  ASSERT_EQ(6, *_entryStub.getInteger(grb::type::T90_EMIN));
  ASSERT_EQ(7, *_entryStub.getInteger(grb::type::T90_EMAX));
  ASSERT_EQ(nullptr, _entryStub.getInteger(grb::type::UNDEFINED_COLUMN));
}

TEST_F(CatalogEntryGrbcatTest, getIndex)
{
  _entryStub.getTimeDef() = 1;
  _entryStub.getObservatory() = 2;
  _entryStub.getRegion() = 3;
  _entryStub.getT50().getMod() = 4;
  _entryStub.getT90().getMod() = 5;

  ASSERT_EQ(1, *_entryStub.getIndex(grb::type::TIME_DEF));
  ASSERT_EQ(2, *_entryStub.getIndex(grb::type::OBSERVATORY));
  ASSERT_EQ(3, *_entryStub.getIndex(grb::type::REGION));
  ASSERT_EQ(4, *_entryStub.getIndex(grb::type::T50_MOD));
  ASSERT_EQ(5, *_entryStub.getIndex(grb::type::T90_MOD));
  ASSERT_EQ(nullptr, _entryStub.getIndex(grb::type::UNDEFINED_COLUMN));
}

TEST_F(CatalogEntryGrbcatTest, getIntegerRange)
{
  _entryStub.getT50().getRange().push_back(1);
  _entryStub.getT50().getRange().push_back(2);
  _entryStub.getT90().getRange().push_back(3);
  _entryStub.getT90().getRange().push_back(4);

  ASSERT_EQ(1, _entryStub.getIntegerRange(grb::type::T50)->front());
  ASSERT_EQ(2, _entryStub.getIntegerRange(grb::type::T50)->back());
  ASSERT_EQ(3, _entryStub.getIntegerRange(grb::type::T90)->front());
  ASSERT_EQ(4, _entryStub.getIntegerRange(grb::type::T90)->back());
  ASSERT_EQ(nullptr, _entryStub.getIntegerRange(grb::type::UNDEFINED_COLUMN));
}

TEST_F(CatalogEntryGrbcatTest, getIndexList)
{
  _entryStub.getReference().push_back(1);
  _entryStub.getReference().push_back(2);
  _entryStub.getReference().push_back(3);

  ASSERT_EQ(1, _entryStub.getIndexList(grb::type::REFERENCE)->front());
  ASSERT_EQ(3, _entryStub.getIndexList(grb::type::REFERENCE)->size());
  ASSERT_EQ(nullptr, _entryStub.getIndexList(grb::type::UNDEFINED_COLUMN));
}

TEST_F(CatalogEntryGrbcatTest, getFloat)
{
  _entryStub.getCoordFlag() = 1.0;
  _entryStub.getCoodinates().getX0() = 2.0;
  _entryStub.getCoodinates().getX2() = 3.0;
  _entryStub.getCoodinates().getX3() = 4.0;
  _entryStub.getT50().getDuration() = 5.0;
  _entryStub.getT50().getError() = 6.0;
  _entryStub.getT90().getDuration() = 7.0;
  _entryStub.getT90().getError() = 8.0;
  _entryStub.getTOther().getDuration() = 9.0;

  ASSERT_DOUBLE_EQ(1.0, *_entryStub.getFloat(grb::type::COORD_FLAG));
  ASSERT_DOUBLE_EQ(2.0, *_entryStub.getFloat(grb::type::TIME));
  ASSERT_DOUBLE_EQ(3.0, *_entryStub.getFloat(grb::type::COORD_RA));
  ASSERT_DOUBLE_EQ(4.0, *_entryStub.getFloat(grb::type::COORD_DEC));
  ASSERT_DOUBLE_EQ(5.0, *_entryStub.getFloat(grb::type::T50));
  ASSERT_DOUBLE_EQ(6.0, *_entryStub.getFloat(grb::type::T50_ERROR));
  ASSERT_DOUBLE_EQ(7.0, *_entryStub.getFloat(grb::type::T90));
  ASSERT_DOUBLE_EQ(8.0, *_entryStub.getFloat(grb::type::T90_ERROR));
  ASSERT_DOUBLE_EQ(9.0, *_entryStub.getFloat(grb::type::T_OTHER));
  ASSERT_EQ(nullptr, _entryStub.getFloat(grb::type::UNDEFINED_COLUMN));
}

TEST_F(CatalogEntryGrbcatTest, getString)
{
  _entryStub.getName() = "1";
  _entryStub.getFluxNotes() = "2";
  _entryStub.getLocalNotes() = "3";
  _entryStub.getTOther().getNotes() = "4";

  ASSERT_STREQ("1", _entryStub.getString(grb::type::NAME)->c_str());
  ASSERT_STREQ("2", _entryStub.getString(grb::type::FLUX_NOTES)->c_str());
  ASSERT_STREQ("3", _entryStub.getString(grb::type::LOCAL_NOTES)->c_str());
  ASSERT_STREQ("4", _entryStub.getString(grb::type::NOTES)->c_str());
  ASSERT_EQ(nullptr, _entryStub.getString(grb::type::UNDEFINED_COLUMN));
}

TEST_F(CatalogEntryGrbcatTest, getStringList)
{
  _entryStub.getAltNames().push_back("1");
  _entryStub.getAltNames().push_back("2");
  _entryStub.getAltNames().push_back("3");

  ASSERT_STREQ("1", _entryStub.getStringList(grb::type::ALT_NAMES)->front().c_str());
  ASSERT_EQ(3, _entryStub.getStringList(grb::type::ALT_NAMES)->size());
  ASSERT_EQ(nullptr, _entryStub.getStringList(grb::type::UNDEFINED_COLUMN));
}

TEST_F(CatalogEntryGrbcatTest, getMapper)
{
  ASSERT_EQ(grb::type::OBSERVATORY, _entryStub.getMapper(grb::type::OBSERVATORY)->getColumnType());
  ASSERT_EQ(grb::type::REFERENCE, _entryStub.getMapper(grb::type::REFERENCE)->getColumnType());
  ASSERT_EQ(grb::type::REGION, _entryStub.getMapper(grb::type::REGION)->getColumnType());
  ASSERT_EQ(grb::type::TIME_DEF, _entryStub.getMapper(grb::type::TIME_DEF)->getColumnType());
  ASSERT_EQ(grb::type::T50_MOD, _entryStub.getMapper(grb::type::T50_MOD)->getColumnType());
  ASSERT_EQ(grb::type::T90_MOD, _entryStub.getMapper(grb::type::T90_MOD)->getColumnType());
  ASSERT_EQ(nullptr, _entryStub.getMapper(grb::type::UNDEFINED_COLUMN));
}

TEST_F(CatalogEntryGrbcatTest, setUnitType)
{
  _entryStub.setUnitType(grb::type::TIME, grb::type::SECOND);
  _entryStub.setUnitType(grb::type::COORD_RA, grb::type::DEGREE);
  _entryStub.setUnitType(grb::type::COORD_DEC, grb::type::NO_UNIT);
  _entryStub.setUnitType(grb::type::T50, grb::type::SECOND);
  _entryStub.setUnitType(grb::type::T50_ERROR, grb::type::SECOND);
  _entryStub.setUnitType(grb::type::T50_EMIN, grb::type::KILO_EV);
  _entryStub.setUnitType(grb::type::T50_EMAX, grb::type::KILO_EV);
  _entryStub.setUnitType(grb::type::T90, grb::type::SECOND);
  _entryStub.setUnitType(grb::type::T90_ERROR, grb::type::SECOND);
  _entryStub.setUnitType(grb::type::T90_EMIN, grb::type::KILO_EV);
  _entryStub.setUnitType(grb::type::T90_EMAX, grb::type::KILO_EV);
  _entryStub.setUnitType(grb::type::T_OTHER, grb::type::SECOND);
  _entryStub.setUnitType(grb::type::UNDEFINED_COLUMN, grb::type::UNDEFINED_UNIT);

  ASSERT_EQ(grb::type::SECOND, _entryStub.getCoodinates().getUnitType(grb::type::X0));
  ASSERT_EQ(grb::type::DEGREE, _entryStub.getCoodinates().getUnitType(grb::type::X2));
  ASSERT_EQ(grb::type::NO_UNIT, _entryStub.getCoodinates().getUnitType(grb::type::X3));
  ASSERT_EQ(grb::type::SECOND, _entryStub.getT50().getDurationUnitType());
  ASSERT_EQ(grb::type::KILO_EV, _entryStub.getT50().getEnergyUnitType());
  ASSERT_EQ(grb::type::SECOND, _entryStub.getT90().getDurationUnitType());
  ASSERT_EQ(grb::type::KILO_EV, _entryStub.getT90().getEnergyUnitType());
  ASSERT_EQ(grb::type::SECOND, _entryStub.getTOther().getDurationUnitType());
}

TEST_F(CatalogEntryGrbcatTest, isValid_Negative)
{
  ASSERT_FALSE(_entryStub.isValid());
}

TEST_F(CatalogEntryGrbcatTest, isValid_Positive)
{
  _entryStub.getRecordNumber() = 1;
  _entryStub.getId() = 2;
  _entryStub.getClassId() = 3;
  _entryStub.getName() = "GRB";
  _entryStub.getCoodinates().getX0() = 1.0;
  ASSERT_TRUE(_entryStub.isValid());
}

} // namespace testing
