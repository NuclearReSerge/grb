#include "Data/DataBaseFormat.h"

#include "Common/Exception.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class DataBaseFormatFactoryType
{
public:
  const DataBaseFormat* getFormat(const type::DatabaseTableType dbType) throw(Exception);

protected:
  friend class Singleton<DataBaseFormatFactoryType>;
  DataBaseFormatFactoryType();

private:
  DataBaseFormat* _HEASARC_GRBCAT;
};

typedef Singleton<DataBaseFormatFactoryType> DataBaseFormatFactory;

}
