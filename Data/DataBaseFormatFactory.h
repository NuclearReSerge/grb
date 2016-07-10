#include "Common/Singleton.h"
#include "Data/DataBaseFormat.h"

#pragma once

namespace grb
{

namespace factory
{

class DataBaseFormatFactory
{
public:
  virtual DataBaseFormat* create(const type::DatabaseTableType type);
  virtual DataBaseFormat* create(const std::string& name);
};

}

typedef Singleton<factory::DataBaseFormatFactory> DataBaseFormatFactory;
}

