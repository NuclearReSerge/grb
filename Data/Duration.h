#include "Common/Global.h"

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

  const type::Index& getMod() const;
  const type::Float& getDuration() const;
  const type::Float& getError() const;
  const type::IntegerRange& getRange() const;
  const type::Integer& getEmin() const;
  const type::Integer& getEmax() const;

protected:
  friend class CatalogEntryGRBCAT;
  type::Index& getMod();
  type::Float& getDuration();
  type::Float& getError();
  type::IntegerRange& getRange();
  type::Integer& getEmin();
  type::Integer& getEmax();

private:
  bool _isPresent;
  type::Index _mod;
  type::Float _duration;
  type::Float _error;
  type::IntegerRange _range;
  type::Integer _emin;
  type::Integer _emax;
};

class DurationOther
{
public:
  DurationOther();
  ~DurationOther();

  bool isPresent() const;
  void setPresent(bool val = true);

  const type::Float& getDuration() const;
  const type::String& getNotes() const;

protected:
  friend class CatalogEntryGRBCAT;
  type::Float& getDuration();
  type::String& getNotes();

private:
  bool _isPresent;
  type::Float _duration;
  type::String _notes;
};

}
