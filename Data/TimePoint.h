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
  const type::Float& getTimeUnix() const;
  const type::Float& getTimeJD() const;
  const type::Float& getTimeMJD() const;

protected:
  friend class CatalogEntryGRBCAT;
  type::Float& getTime();
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
