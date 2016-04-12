#include "Data/DataBaseFormat.h"

#pragma once


namespace grb
{

class DataBaseFormatGrbcat : public DataBaseFormat
{
public:
  DataBaseFormatGrbcat();
  type::CoordinateSystemType getCoordinateSystem() const;

protected:
  void initialize();

private:
  type::CoordinateSystemType _coordSys;
};

}
