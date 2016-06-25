#include "Data/CatalogEntryGrbcat.h"

#include "Data/Observatory.h"
#include "Data/Reference.h"
#include "Data/Region.h"
#include "Data/TimeDef.h"
#include "Data/TimeMod.h"

namespace grb
{

CatalogEntryGRBCAT::CatalogEntryGRBCAT(const Catalog& catalog)
  : CatalogEntry(catalog),
    _record_number(0), _id(0), _time(type::MODIFIED_JULIAN_DATE), _time_def(-1),
    _observatory(-1), _coordinates(type::EQUATORIAL_J2000), _region(-1),
    _afterglow_flag(false), _t50(), _t90(), _t_other(), _flux_flag(false), _class_id(0)
{ }

type::Integer&
CatalogEntryGRBCAT::getRecordNumber()
{
  return _record_number;
}

type::Integer&
CatalogEntryGRBCAT::getId()
{
  return _id;
}

type::String&
CatalogEntryGRBCAT::getName()
{
  return _name;
}

type::StringList&
CatalogEntryGRBCAT::getAltNames()
{
  return _alt_names;
}

TimePoint&
CatalogEntryGRBCAT::getTime()
{
  return _time;
}

type::Index&
CatalogEntryGRBCAT::getTimeDef()
{
  return _time_def;
}

type::Index&
CatalogEntryGRBCAT::getObservatory()
{
  return _observatory;
}

type::Float&
CatalogEntryGRBCAT::getCoordFlag()
{
  return _coord_flag;
}

Coordinates&
CatalogEntryGRBCAT::getCoodinates()
{
  return _coordinates;
}

type::Index&
CatalogEntryGRBCAT::getRegion()
{
  return _region;
}

type::Flag&
CatalogEntryGRBCAT::getAfterglowFlag()
{
  return _afterglow_flag;
}

type::IndexList&
CatalogEntryGRBCAT::getReference()
{
  return _reference;
}

Duration&
CatalogEntryGRBCAT::getT50()
{
  return _t50;
}

Duration&
CatalogEntryGRBCAT::getT90()
{
  return _t90;
}

DurationOther&
CatalogEntryGRBCAT::getTOther()
{
  return _t_other;
}

type::Flag&
CatalogEntryGRBCAT::getFluxFlag()
{
  return _flux_flag;
}

type::String&
CatalogEntryGRBCAT::getFluxNotes()
{
  return _flux_notes;
}

type::String&
CatalogEntryGRBCAT::getLocalNotes()
{
  return _local_notes;
}

type::Integer&
CatalogEntryGRBCAT::getClassId()
{
  return _class_id;
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
      return &_t50.getEmin();
    case type::T50_EMAX:
      return &_t50.getEmax();
    case type::T90_EMIN:
      return &_t90.getEmin();
    case type::T90_EMAX:
      return &_t90.getEmax();
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
      return &_t50.getMod();
    case type::T90_MOD:
      return &_t90.getMod();
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
      return &_t50.getRange();
    case type::T90:
      return &_t90.getRange();
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
      return &_coordinates.getX2();
    case type::COORD_DEC:
      return &_coordinates.getX3();
    case type::COORD_FLAG:
      return &_coord_flag;
    case type::TIME:
      return &_time.getX0();
    case type::T50:
      return &_t50.getDuration();
    case type::T50_ERROR:
      return &_t50.getError();
    case type::T90:
      return &_t90.getDuration();
    case type::T90_ERROR:
      return &_t90.getError();
    case type::T_OTHER:
      return &_t_other.getDuration();
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
      return &_t_other.getNotes();
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

void
CatalogEntryGRBCAT::setUnitType(type::ColumnType column, type::UnitType unitType)
{
  switch (column)
  {
    case type::COORD_RA:
      _coordinates.setX2UnitType(unitType);
      break;
    case type::COORD_DEC:
      _coordinates.setX3UnitType(unitType);
      break;
    case type::TIME:
      _time.setTimeUnitType(unitType);
      break;
    case type::T50:
    case type::T50_ERROR:
      _t50.setDurationUnitType(unitType);
      break;
    case type::T50_EMIN:
    case type::T50_EMAX:
      _t50.setEnergyUnitType(unitType);
      break;
    case type::T90:
    case type::T90_ERROR:
      _t90.setDurationUnitType(unitType);
      break;
    case type::T90_EMIN:
    case type::T90_EMAX:
      _t90.setEnergyUnitType(unitType);
      break;
    case type::T_OTHER:
      _t_other.setDurationUnitType(unitType);
      break;
    default:
      break;
  }
}

bool
CatalogEntryGRBCAT::isValid()
{
  return _record_number && _id && _class_id &&
      _name[0] == 'G' && _name[1] == 'R' && _name[2] == 'B' &&
      _time.isValid() &&
      _coordinates.isValid() &&
      _t50.isValid() &&
      _t90.isValid() &&
      _t_other.isValid();
}

}
