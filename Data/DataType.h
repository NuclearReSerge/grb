#include "Common/Global.h"

#pragma once

namespace grb
{

class DataType
{
public:
  DataType()
    : _columnType(type::COLUMN_TYPE_UNDEFINED), _isRequired(false),
      _unitType(type::UNIT_TYPE_UNDEFINED), _valueType(type::VALUE_TYPE_UNDEFINED)
  { }
  DataType(type::ColumnType columnType, bool isRequired, type::UnitType unitType,
           type::ValueType valueType)
    : _columnType(columnType), _isRequired(isRequired), _unitType(unitType), _valueType(valueType)
  { }

  type::ColumnType getColumnType() const
  {
    return _columnType;
  }
  bool isColumnRequired() const
  {
    return _isRequired;
  }
  type::UnitType getUnitType() const
  {
    return _unitType;
  }
  type::ValueType getValueType() const
  {
    return _valueType;
  }

private:
  const type::ColumnType _columnType;
  const bool _isRequired;
  const type::UnitType _unitType;
  const type::ValueType _valueType;
};


template <typename T>
class DataTypeWithRangeCheck : public DataType
{
public:
  DataTypeWithRangeCheck()
    : DataType(), _hasValueRange(false), _minValue(T()), _maxValue(T())
  { }
  DataTypeWithRangeCheck(type::ColumnType columnType, bool isRequired, type::UnitType unitType,
                         type::ValueType valueType, bool hasValueRange, const T& minValue,
                         const T& maxValue)
    : DataType(columnType, isRequired, unitType, valueType), _hasValueRange(hasValueRange),
      _minValue(minValue), _maxValue(maxValue)
  { }

  bool hasValueRange() const
  {
    return _hasValueRange;
  }
  bool checkRange(const T& value) const
  {
    if (!_hasValueRange)
      return true;
    return isInRange(value);
  }

protected:
  bool isInRange(const T& value);

private:
  const bool _hasValueRange;
  const T _minValue;
  const T _maxValue;
};

typedef DataTypeWithRangeCheck<std::string> DataTypeString;
typedef DataTypeWithRangeCheck<type::Date> DataTypeDate;
typedef DataTypeWithRangeCheck<double> DataTypePosition;
typedef DataTypeWithRangeCheck<std::size_t> DataTypeInteger;
typedef DataTypeWithRangeCheck<bool> DataTypeFlag;
typedef DataTypeWithRangeCheck<double> DataTypeFloat;

}
