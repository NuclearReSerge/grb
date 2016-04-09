#include "Data/DataBaseFormat.h"

#pragma once


namespace grb
{

class DataBaseFormatGrbcat : public DataBaseFormat
{
public:
  DataBaseFormatGrbcat() = delete;
  DataBaseFormatGrbcat(const type::DatabaseTableType dbType);

  void initialize() throw(Exception);
};

}
