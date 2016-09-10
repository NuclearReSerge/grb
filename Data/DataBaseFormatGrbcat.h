#include "Data/Coordinates.h"
#include "Data/DataBaseFormat.h"

#pragma once


namespace grb
{

class DataBaseFormatGrbcat : public DataBaseFormat
{
public:
  DataBaseFormatGrbcat()
    : DataBaseFormat(type::HEASARC_GRBCAT), _coordSys(type::EQUATORIAL_J2000)
  {
  }

  type::CoordinateSystemType getCoordinateSystem() const
  {
    return _coordSys;
  }

  void initialize();

private:
  type::CoordinateSystemType _coordSys;
};

} // namespace grb
