#include "Common/Singleton.h"
#include "Data/DataBaseFormatMapper.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum CatalogEntryType
{
  GRBCAT_ENTRY,

  // TEST
  TEST_CATALOG_ENTRY,

  // LAST
  UNDEFINED_CATALOG_ENTRY
};

}

namespace mapper
{

class CatalogEntryMapper : public Mapper<type::CatalogEntryType>
{
public:
  CatalogEntryMapper();
  type::CatalogEntryType convertDataBaseFormat(type::DatabaseTableType dbType);

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::CatalogEntryMapper> CatalogEntryMapper;

}
