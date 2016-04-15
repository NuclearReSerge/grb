#include "Duration.h"

namespace grb
{

/** ************************************************************************************************
 *
 *
 *
 **************************************************************************************************/

Duration::Duration()
  : _isPresent(false), _mod(-1), _duration(0.0), _error(0.0), _emin(0), _emax(0),
    _durationUnitType(type::UNIT_TYPE_UNDEFINED), _energyUnitType(type::UNIT_TYPE_UNDEFINED)
{
}

Duration::~Duration()
{
  _range.clear();
}

bool
Duration::isPresent() const
{
  return _isPresent;
}

void
Duration::setPresent(bool val)
{
  _isPresent = val;
}

const type::Index&
Duration::getMod() const
{
  return _mod;
}

const type::Float&
Duration::getDuration() const
{
  return _duration;
}

const type::Float&
Duration::getError() const
{
  return _error;
}

const type::IntegerRange&
Duration::getRange() const
{
  return _range;
}

const type::Integer&
Duration::getEmin() const
{
  return _emin;
}

const type::Integer&
Duration::getEmax() const
{
  return _emax;
}

type::Index&
Duration::getMod()
{
  return _mod;
}

type::Float&
Duration::getDuration()
{
  return _duration;
}

type::Float&
Duration::getError()
{
  return _error;
}

type::IntegerRange&
Duration::getRange()
{
  return _range;
}

type::Integer&
Duration::getEmin()
{
  return _emin;
}

type::Integer&
Duration::getEmax()
{
  return _emax;
}

void
Duration::setDurationUnitType(type::UnitType unitType)
{
  _durationUnitType = unitType;
}

void
Duration::setEnergyUnitType(type::UnitType unitType)
{
  _energyUnitType = unitType;
}

bool
Duration::isValid()
{
  return true;
}

/** ************************************************************************************************
 *
 *
 *
 **************************************************************************************************/

DurationOther::DurationOther()
  : _isPresent(false), _duration(0.0), _durationUnitType(type::UNIT_TYPE_UNDEFINED)
{ }

DurationOther::~DurationOther()
{ }

bool
DurationOther::isPresent() const
{
  return _isPresent;
}

void
DurationOther::setPresent(bool val)
{
  _isPresent = val;
}

const type::Float&
DurationOther::getDuration() const
{
  return _duration;
}

const type::String&
DurationOther::getNotes() const
{
  return _notes;
}

type::Float&
DurationOther::getDuration()
{
  return _duration;
}

type::String&
DurationOther::getNotes()
{
  return _notes;
}

void
DurationOther::setDurationUnitType(type::UnitType unitType)
{
  _durationUnitType = unitType;
}

bool
DurationOther::isValid()
{
  return true;
}

}
