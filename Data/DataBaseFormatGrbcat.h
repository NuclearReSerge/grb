#include "Data/Coordinates.h"
#include "Data/DataBaseFormat.h"

#pragma once


namespace grb
{

class DataBaseFormatGrbcat : public DataBaseFormat
{
public:
  DataBaseFormatGrbcat();

  void initialize();
  type::CoordinateSystemType getCoordinateSystem() const;


private:
  type::CoordinateSystemType _coordSys;
};

}
