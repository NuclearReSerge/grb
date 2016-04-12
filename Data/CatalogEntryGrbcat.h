#include "Data/CatalogEntry.h"

#include "Data/Coordinates.h"
#include "Data/Duration.h"
#include "Data/TimePoint.h"

#pragma once

namespace grb
{

class CatalogEntryGRBCAT : public CatalogEntry
{
public:
  CatalogEntryGRBCAT();

  const type::Integer& getRecordNumber() const;
  const type::Integer& getId() const;
  const type::String& getName() const;
  const type::StringList& getAltNames() const;
  const TimePoint& getTime() const;
  const type::Index& getTimeDef() const;
  const type::Index& getObservatory() const;
  const Coordinates& getCoodinates() const;
  const type::Index& getRegion() const;
  const type::Flag& getAfterglowFlag() const;
  const type::IndexList& getReference() const;
  const Duration& getT50() const;
  const Duration& getT90() const;
  const DurationOther& getTOther() const;
  const type::Flag& getFluxFlag() const;
  const type::String& getFluxNotes() const;
  const type::String& getLocalNotes() const;
  const type::Integer& getClassId() const;

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
