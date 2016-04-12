#include "Data/CatalogEntry.h"
#include "Data/CatalogEntryStructures.h"

#pragma once

namespace grb
{

class CatalogEntryGRBCAT : public CatalogEntry
{
public:
  CatalogEntryGRBCAT();

  const type::Integer& getRecordNumber() const { return _record_number; }
  const type::Integer& getId() const { return _id; }
  const type::String& getName() const { return _name; }
  const type::StringList& getAltNames() const { return _alt_names; }
  const TimePoint& getTime() const { return _time; }
  const type::Index& getTimeDef() const { return _time_def; }
  const type::Index& getObservatory() const { return _observatory; }
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

protected:
  type::Flag* getFlag(type::ColumnType column);
  type::Integer* getInteger(type::ColumnType column);
  type::Index* getIndex(type::ColumnType column);
  type::IntegerRange* getIntegerRange(type::ColumnType column);
  type::IndexList* getIndexList(type::ColumnType column);
  type::Float* getFloat(type::ColumnType column);
  type::String* getString(type::ColumnType column);
  type::StringList* getStringList(type::ColumnType column);
  NameMapper* getMapper(type::ColumnType column);
  bool isValid();

private:
  type::Integer _record_number;
  type::Integer _id;
  type::String _name;
  type::StringList _alt_names;
  TimePoint _time;
  type::Index _time_def;
  type::Index _observatory;
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

}
