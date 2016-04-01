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

}
