#include "Common/Global.h"

#pragma once

namespace grb
{

class TimePoint
{
public:
  TimePoint(type::DateTimeType type = type::DATE_TIME_TYPE_UNDEFINED);

  type::DateTimeType getType() const;

  const type::Float& getTime() const;
  const type::Float& getTimeJD() const;
  const type::Float& getTimeMJD() const;

protected:
  friend class CatalogEntryGRBCAT;
  type::Float& getTime();

private:
  type::DateTimeType _type;
  type::Float _time;
};

}
