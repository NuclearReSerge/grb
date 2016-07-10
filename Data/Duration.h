#include "Common/Global.h"
#include "Data/UnitMapper.h"

#pragma once

namespace grb
{

class Duration
{
public:
  Duration();
  ~Duration();

  bool isPresent() const;
  void setPresent(bool val = true);

  type::Index& getMod();
  type::Float& getDuration();
  type::Float& getError();
  type::IntegerRange& getRange();
  type::Integer& getEmin();
  type::Integer& getEmax();

protected:
  friend class CatalogEntryGrbcat;
  void setDurationUnitType(type::UnitType unitType);
  void setEnergyUnitType(type::UnitType unitType);

  bool isValid();

private:
  bool _isPresent;
  type::Index _mod;
  type::Float _duration;
  type::Float _error;
  type::IntegerRange _range;
  type::Integer _emin;
  type::Integer _emax;
  type::UnitType _durationUnitType;
  type::UnitType _energyUnitType;

};

class DurationOther
{
public:
  DurationOther();
  ~DurationOther();

  bool isPresent() const;
  void setPresent(bool val = true);

  type::Float& getDuration();
  type::String& getNotes();

protected:
  friend class CatalogEntryGrbcat;
  void setDurationUnitType(type::UnitType unitType);

  bool isValid();

private:
  bool _isPresent;
  type::Float _duration;
  type::UnitType _durationUnitType;
  type::String _notes;
};

}
