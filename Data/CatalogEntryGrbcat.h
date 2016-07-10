#include "Data/CatalogEntry.h"

#include "Data/Coordinates.h"
#include "Data/Duration.h"

#pragma once

namespace grb
{

class CatalogEntryGrbcat : public CatalogEntry
{
public:
  CatalogEntryGrbcat();

  type::Integer& getRecordNumber();
  type::Integer& getId();
  type::String& getName();
  type::StringList& getAltNames();
  type::Index& getTimeDef();
  type::Index& getObservatory();
  type::Float& getCoordFlag();
  Coordinates& getCoodinates();
  type::Index& getRegion();
  type::Flag& getAfterglowFlag();
  type::IndexList& getReference();
  Duration& getT50();
  Duration& getT90();
  DurationOther& getTOther();
  type::Flag& getFluxFlag();
  type::String& getFluxNotes();
  type::String& getLocalNotes();
  type::Integer& getClassId();

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

  void setUnitType(type::ColumnType column, type::UnitType unitType);

  bool isValid();

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

}
