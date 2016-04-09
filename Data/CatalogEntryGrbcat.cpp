#include "Data/CatalogEntryGrbcat.h"

#include "Data/Observatory.h"
#include "Data/Reference.h"
#include "Data/Region.h"
#include "Data/TimeDef.h"
#include "Data/TimeMod.h"

namespace grb
{

CatalogEntryGRBCAT::CatalogEntryGRBCAT()
  : CatalogEntry(type::GRBCAT)
{
  _record_number = 0;
  _id = 0;
  _time_def = 0;
  _observatory = 0;
  _coordinates.coord_flag = false;
  _coordinates.systemType = type::COORDINATE_SYSTEM_UNDEFINED;
  _coordinates.u.undefined.horizontal = 0.0;
  _coordinates.u.undefined.vertical = 0.0;
  _region = 0;
  _afterglow_flag = false;
  _t50.isPresent = false;
  _t50.mod = 0;
  _t50.value = 0.0;
  _t50.error = 0.0;
  _t50.emin = 0;
  _t50.emax = 0.0;
  _t90.isPresent = false;
  _t90.mod = 0;
  _t90.value = 0.0;
  _t90.error = 0.0;
  _t90.emin = 0;
  _t90.emax = 0.0;
  _t_other.isPresent = false;
  _t_other.value = 0.0;
  _flux_flag = false;
  _class_id = 0;
}

type::Flag*
CatalogEntryGRBCAT::getFlag(type::ColumnType column)
{
  switch (column)
  {
    case type::AFTERGLOW_FLAG:
      return &_afterglow_flag;
    case type::FLUX_FLAG:
      return &_flux_flag;
    default:
      break;
  }
  return nullptr;
}

type::Integer*
CatalogEntryGRBCAT::getInteger(type::ColumnType column)
{
  switch (column)
  {
    case type::RECORD_NUMBER:
      return &_record_number;
    case type::ID:
      return &_id;
    case type::T50_EMIN:
      return &_t50.emin;
    case type::T50_EMAX:
      return &_t50.emax;
    case type::T90_EMIN:
      return &_t90.emin;
    case type::T90_EMAX:
      return &_t90.emax;
    case type::CLASS:
      return &_class_id;
    default:
      break;
  }
  return nullptr;
}

type::Index*
CatalogEntryGRBCAT::getIndex(type::ColumnType column)
{
  switch (column)
  {
    case type::TIME_DEF:
      return &_time_def;
    case type::OBSERVATORY:
      return &_observatory;
    case type::REGION:
      return &_region;
    case type::T50_MOD:
      return &_t50.mod;
    case type::T90_MOD:
      return &_t90.mod;
    default:
      break;
  }
  return nullptr;
}

type::IntegerRange*
CatalogEntryGRBCAT::getIntegerRange(type::ColumnType column)
{
  switch (column)
  {
    case type::T50:
      return &_t50.range;
    case type::T90:
      return &_t90.range;
    default:
      break;
  }
  return nullptr;
}

type::IndexList*
CatalogEntryGRBCAT::getIndexList(type::ColumnType column)
{
  switch (column)
  {
    case type::REFERENCE:
      return &_reference;
    default:
      break;
  }
  return nullptr;
}

type::Float*
CatalogEntryGRBCAT::getFloat(type::ColumnType column)
{
  switch (column)
  {
    case type::COORD_RA:
      return &_coordinates.u.j2000.rightAscension;
    case type::COORD_DEC:
      return &_coordinates.u.j2000.declination;
    case type::COORD_FLAG:
      return &_coordinates.coord_flag;
    case type::T50:
      return &_t50.value;
    case type::T50_ERROR:
      return &_t50.error;
    case type::T90:
      return &_t90.value;
    case type::T90_ERROR:
      return &_t90.error;
    case type::T_OTHER:
      return &_t_other.value;
    default:
      break;
  }
  return nullptr;
}

type::TimePoint*
CatalogEntryGRBCAT::getTimePoint(type::ColumnType column)
{
  switch (column)
  {
    case type::TIME:
      return &_time;
    default:
      break;
  }
  return nullptr;
}

type::String*
CatalogEntryGRBCAT::getString(type::ColumnType column)
{
  switch (column)
  {
    case type::NAME:
      return &_name;
    case type::NOTES:
      return &_t_other.notes;
    case type::FLUX_NOTES:
      return &_flux_notes;
    case type::LOCAL_NOTES:
      return &_local_notes;
    default:
      break;
  }
  return nullptr;
}

type::StringList*
CatalogEntryGRBCAT::getStringList(type::ColumnType column)
{
  switch (column)
  {
    case type::ALT_NAMES:
      return &_alt_names;
    default:
      break;
  }
  return nullptr;
}

NameMapper*
CatalogEntryGRBCAT::getMapper(type::ColumnType column)
{
  switch (column)
  {
    case type::OBSERVATORY:
      return Observatory::instance();
    case type::REFERENCE:
      return Reference::instance();
    case type::REGION:
      return Region::instance();
    case type::TIME_DEF:
      return TimeDef::instance();
    case type::T50_MOD:
      return Time50Mod::instance();
    case type::T90_MOD:
      return Time90Mod::instance();
    default:
      break;
  }
  return nullptr;
}

}
