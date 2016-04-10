#include "Common/Exception.h"
#include "Common/Global.h"
#include "Common/Singleton.h"

#include <map>

#pragma once

namespace grb
{

class DataBaseFormat;

class DataBaseFormatFactoryType
{
public:
  ~DataBaseFormatFactoryType();

  const DataBaseFormat& getFormat(const type::DatabaseTableType dbType) throw(Exception);

protected:
  friend class Singleton<DataBaseFormatFactoryType>;
  DataBaseFormatFactoryType();
  void initialize();

private:
  std::map<type::DatabaseTableType, DataBaseFormat*> _formatMap;
};

typedef Singleton<DataBaseFormatFactoryType> DataBaseFormatFactory;

}
