#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum ValueType
{
  FLAG,
  INTEGER,
  INDEX,
  INTEGER_RANGE,
  INDEX_LIST,
  FLOAT,
  STRING,
  STRING_LIST,

  // LAST
  UNDEFINED_VALUE
};

}

namespace mapper
{

class ValueMapper : public Mapper<type::ValueType>
{
public:
  ValueMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::ValueMapper> ValueMapper;

}

