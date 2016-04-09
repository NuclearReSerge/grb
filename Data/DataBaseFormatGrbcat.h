#include "Data/DataBaseFormat.h"

#pragma once


namespace grb
{

class DataBaseFormatGrbcat : public DataBaseFormat
{
public:
  DataBaseFormatGrbcat();

protected:
  void initialize();
};

}
