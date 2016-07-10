#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum DateType
{
  UNIX_DATE,
  JULIAN_DATE,
  MODIFIED_JULIAN_DATE,

  // LAST
  UNDEFINED_DATE
};

}

namespace mapper
{

class DateMapper : public Mapper<type::DateType>
{
public:
  DateMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::DateMapper> DateMapper;

}

