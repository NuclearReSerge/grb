#include "Data/CatalogEntryGrbcat.h"

#include "Data/Observatory.h"
#include "Data/Reference.h"
#include "Data/Region.h"
#include "Data/TimeDef.h"
#include "Data/TimeMod.h"

namespace grb
{

CatalogEntryGrbcat::CatalogEntryGrbcat()
  : CatalogEntry(type::GRBCAT_ENTRY),
    _record_number(0), _id(0), _time_def(-1),
    _observatory(-1), _coordinates(type::EQUATORIAL_J2000, type::MODIFIED_JULIAN_DATE),
    _region(-1),
    _afterglow_flag(false), _t50(), _t90(), _t_other(), _flux_flag(false), _class_id(0)
{ }

type::Integer&
CatalogEntryGrbcat::getRecordNumber()
{
  return _record_number;
}

type::Integer&
CatalogEntryGrbcat::getId()
{
  return _id;
}

type::String&
CatalogEntryGrbcat::getName()
{
  return _name;
}

type::StringList&
CatalogEntryGrbcat::getAltNames()
{
  return _alt_names;
}

type::Index&
CatalogEntryGrbcat::getTimeDef()
{
  return _time_def;
}

type::Index&
CatalogEntryGrbcat::getObservatory()
{
  return _observatory;
}

type::Float&
CatalogEntryGrbcat::getCoordFlag()
{
  return _coord_flag;
}

Coordinates&
CatalogEntryGrbcat::getCoodinates()
{
  return _coordinates;
}

type::Index&
CatalogEntryGrbcat::getRegion()
{
  return _region;
}

type::Flag&
CatalogEntryGrbcat::getAfterglowFlag()
{
  return _afterglow_flag;
}

type::IndexList&
CatalogEntryGrbcat::getReference()
{
  return _reference;
}

Duration&
CatalogEntryGrbcat::getT50()
{
  return _t50;
}

Duration&
CatalogEntryGrbcat::getT90()
{
  return _t90;
}

DurationOther&
CatalogEntryGrbcat::getTOther()
{
  return _t_other;
}

type::Flag&
CatalogEntryGrbcat::getFluxFlag()
{
  return _flux_flag;
}

type::String&
CatalogEntryGrbcat::getFluxNotes()
{
  return _flux_notes;
}

type::String&
CatalogEntryGrbcat::getLocalNotes()
{
  return _local_notes;
}

type::Integer&
CatalogEntryGrbcat::getClassId()
{
  return _class_id;
}

type::Flag*
CatalogEntryGrbcat::getFlag(type::ColumnType column)
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
CatalogEntryGrbcat::getInteger(type::ColumnType column)
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
CatalogEntryGrbcat::getIndex(type::ColumnType column)
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
CatalogEntryGrbcat::getIntegerRange(type::ColumnType column)
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
CatalogEntryGrbcat::getIndexList(type::ColumnType column)
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
CatalogEntryGrbcat::getFloat(type::ColumnType column)
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
      return &_coordinates.getX0();
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
CatalogEntryGrbcat::getString(type::ColumnType column)
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
CatalogEntryGrbcat::getStringList(type::ColumnType column)
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
CatalogEntryGrbcat::getMapper(type::ColumnType column)
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
CatalogEntryGrbcat::setUnitType(type::ColumnType column, type::UnitType unitType)
{
  switch (column)
  {
    case type::COORD_RA:
      _coordinates.setUnitType(type::X2, unitType);
      break;
    case type::COORD_DEC:
      _coordinates.setUnitType(type::X3, unitType);
      break;
    case type::TIME:
      _coordinates.setUnitType(type::X0, unitType);
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
CatalogEntryGrbcat::isValid()
{
  return _record_number && _id && _class_id &&
      _name[0] == 'G' && _name[1] == 'R' && _name[2] == 'B' &&
      _coordinates.isValid() &&
      _t50.isValid() &&
      _t90.isValid() &&
      _t_other.isValid();
}

}
