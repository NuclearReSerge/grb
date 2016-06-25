#include "Common/Global.h"

#pragma once

namespace grb
{

class TimePoint
{
public:
  TimePoint(type::DateTimeType type = type::DATE_TIME_TYPE_UNDEFINED);

  type::DateTimeType getType() const;

  // general
  type::Float& getX0();

  // default
  type::Float getTime();
  // system date
  type::Float getTimeUnix();
  // Julian Date
  type::Float getTimeJD();
  type::Float getTimeMJD();

protected:
  friend class CatalogEntryGRBCAT;
  void setTimeUnitType(type::UnitType unitType);

  bool isValid();

  type::Float convertJDtoMJD();
  type::Float convertJDtoUNIX();
  type::Float convertMJDtoJD();
  type::Float convertMJDtoUNIX();
  type::Float convertUNIXtoJD();
  type::Float convertUNIXtoMJD();

private:
  type::DateTimeType _type;
  type::Float _time;
  type::UnitType _timeUnitType;
};

}
