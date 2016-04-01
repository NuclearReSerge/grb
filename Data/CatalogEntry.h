#include "Common/Global.h"


#include <string>
#include <vector>

#pragma once

namespace grb
{

struct CoordinateSystemUndefined
{
  type::Coordinate horizontal;
  type::Coordinate vertical;
};

struct CoordinateSystemEquinox
{
  type::Coordinate rightAscension;
  type::Coordinate declination;
};

struct CoordinateSystemGalactic
{
  type::Coordinate latitude;
  type::Coordinate longitude;
};

struct Coordinates
{
  type::CoordinateSystemType systemType;
  union
  {
    CoordinateSystemUndefined undefined;
    CoordinateSystemEquinox b1950;
    CoordinateSystemEquinox j2000;
    CoordinateSystemGalactic galactic;
  } u;
  type::Float coord_flag;
};

struct Duration
{
  bool isPresent;
  type::Index mod;
  type::Float value;
  type::Float error;
  type::IntegerRange range;
  type::Integer emin;
  type::Integer emax;
};

struct DurationOther
{
  bool isPresent;
  type::Float value;
  type::String notes;
};

struct CatalogEntry
{
  type::Integer record_number;
  type::Integer id;
  type::String name;
  type::StringList alt_names;
  type::TimePoint time;
  type::Index time_def; // TimeDef::instance()
  type::Index observatory; // Observatory::instance()
  Coordinates coordinates;
  type::Index region;   // Region::instance()
  type::Flag afterglow_flag;
  type::IndexList reference; // Reference::instance()
  Duration t50;
  Duration t90;
  DurationOther t_other;
  type::Flag flux_flag;
  type::String flux_notes;
  type::String local_notes;
  type::Integer class_id;
};

}
