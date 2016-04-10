#include "Data/CatalogEntry.h"
#include "Data/CatalogEntryStructures.h"

#pragma once

namespace grb
{

class CatalogEntryGRBCAT : public CatalogEntry
{
public:
  CatalogEntryGRBCAT();

  type::Flag* getFlag(type::ColumnType column);
  type::Integer* getInteger(type::ColumnType column);
  type::Index* getIndex(type::ColumnType column);
  type::IntegerRange* getIntegerRange(type::ColumnType column);
  type::IndexList* getIndexList(type::ColumnType column);
  type::Float* getFloat(type::ColumnType column);
  type::String* getString(type::ColumnType column);
  type::StringList* getStringList(type::ColumnType column);

  NameMapper* getMapper(type::ColumnType column);

protected:
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
