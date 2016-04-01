#include "Data/DataType.h"

namespace grb
{

template <>
bool
DataTypeWithRangeCheck<std::string>::isInRange(const std::string& value)
{
  return !value.empty();
}

template <>
bool
DataTypeWithRangeCheck<type::Date>::isInRange(const type::Date& value)
{
  return value >= _minValue && value <= _maxValue;
}

template <>
bool
DataTypeWithRangeCheck<double>::isInRange(const double& value)
{
  return value >= _minValue && value <= _maxValue;
}

template <>
bool
DataTypeWithRangeCheck<std::size_t>::isInRange(const std::size_t& value)
{
  return value >= _minValue && value < _maxValue;
}

template <>
bool
DataTypeWithRangeCheck<bool>::isInRange(const bool& value)
{
  // unused parameter 'value'
  return value == true || value == false;
}

}
