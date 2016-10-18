#include "Data/CatalogEntry.h"
#include "Data/Coordinates.h"
#include "Data/Duration.h"

#pragma once

namespace grb
{

class CatalogEntryGrbcat : public CatalogEntry
{
public:
  CatalogEntryGrbcat()
    : CatalogEntry(type::GRBCAT),
      _record_number(0), _id(0),
      _time_def(-1),
      _observatory(-1),
      _coord_flag(0.0), _coordinates(type::EQUATORIAL_J2000, type::MODIFIED_JULIAN_DATE),
      _region(-1),
      _afterglow_flag(false), _t50(), _t90(), _t_other(), _flux_flag(false), _class_id(0)
  {
  }

  type::Integer& getRecordNumber() { return _record_number; }
  type::Integer& getId() { return _id; }
  type::String& getName() { return _name; }
  type::StringList& getAltNames() { return _alt_names; }
  type::Index& getTimeDef() { return _time_def; }
  type::Index& getObservatory() { return _observatory; }
  type::Float& getCoordFlag() { return _coord_flag; }
  Coordinates& getCoodinates() { return _coordinates; }
  type::Index& getRegion() { return _region; }
  type::Flag& getAfterglowFlag() { return _afterglow_flag; }
  type::IndexList& getReference() { return _reference; }
  Duration& getT50() { return _t50; }
  Duration& getT90() { return _t90; }
  DurationOther& getTOther() { return _t_other; }
  type::Flag& getFluxFlag() { return _flux_flag; }
  type::String& getFluxNotes() { return _flux_notes; }
  type::String& getLocalNotes() { return _local_notes; }
  type::Integer& getClassId() { return _class_id; }

  const type::Integer& getRecordNumber() const { return _record_number; }
  const type::Integer& getId() const { return _id; }
  const type::String& getName() const { return _name; }
  const type::StringList& getAltNames() const { return _alt_names; }
  const type::Index& getTimeDef() const { return _time_def; }
  const type::Index& getObservatory() const { return _observatory; }
  const type::Float& getCoordFlag() const { return _coord_flag; }
  const Coordinates& getCoodinates() const { return _coordinates; }
  const type::Index& getRegion() const { return _region; }
  const type::Flag& getAfterglowFlag() const { return _afterglow_flag; }
  const type::IndexList& getReference() const { return _reference; }
  const Duration& getT50() const { return _t50; }
  const Duration& getT90() const { return _t90; }
  const DurationOther& getTOther() const { return _t_other; }
  const type::Flag& getFluxFlag() const { return _flux_flag; }
  const type::String& getFluxNotes() const { return _flux_notes; }
  const type::String& getLocalNotes() const { return _local_notes; }
  const type::Integer& getClassId() const { return _class_id; }

  bool isValid();

protected:
  type::Flag* getFlag(type::ColumnType column);
  type::Integer* getInteger(type::ColumnType column);
  type::Index* getIndex(type::ColumnType column);
  type::IntegerRange* getIntegerRange(type::ColumnType column);
  type::IndexList* getIndexList(type::ColumnType column);
  type::Float* getFloat(type::ColumnType column);
  type::String* getString(type::ColumnType column);
  type::StringList* getStringList(type::ColumnType column);

  mapper::NameMapper* getMapper(type::ColumnType column);

  void setUnitType(type::ColumnType column, type::UnitType unitType);

private:
  type::Integer _record_number;
  type::Integer _id;
  type::String _name;
  type::StringList _alt_names;
  type::Index _time_def;
  type::Index _observatory;
  type::Float _coord_flag;
  Coordinates _coordinates;
  type::Index _region;
  type::Flag _afterglow_flag;
  type::IndexList _reference;
  Duration _t50;
  Duration _t90;
  DurationOther _t_other;
  type::Flag _flux_flag;
  type::String _flux_notes;
  type::String _local_notes;
  type::Integer _class_id;
};

} // namespace grb
