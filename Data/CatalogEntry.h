#include "Common/Global.h"


#include <string>
#include <vector>

#pragma once

namespace grb
{

struct CoordinateSystemUndefined
{
  double horizontal;
  double vertical;
};

struct CoordinateSystemEquinox
{
  double rightAscension;
  double declination;
};

struct CoordinateSystemGalactic
{
  double latitude;
  double longitude;
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
  double coord_flag;
};

struct Duration
{
  bool isPresent;
  type::Index mod;
  double value;
  double error;
  std::size_t range[2];
  std::size_t emin;
  std::size_t emax;
};

struct DurationOther
{
  bool isPresent;
  double value;
  std::string notes;
};

struct CatalogEntry
{
  std::string name;
  type::Date time;
  type::Index observatory; // Observatory::instance()
  Coordinates coordinates;
  type::Index region;   // Region::instance()
  bool afterglow_flag;
  bool flux_flag;
  std::size_t id;
  std::size_t record_number;
  std::vector<std::string> alt_names;
  type::Index time_def; // TimeDef::instance()
  std::vector<type::Index> reference; // Reference::instance()
  Duration t50;
  Duration t90;
  DurationOther t_other;
  std::string flux_notes;
  std::string local_notes;
};

}
