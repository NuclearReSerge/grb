#include "Data/ColumnType.h"
#include "Data/UnitType.h"
#include "Data/ValueType.h"

#include <bitset>
#include <vector>

#pragma once

namespace grb
{

namespace type
{

typedef std::bitset<type::UNDEFINED_COLUMN> ColumnFlags;

}

class DataBaseColumn
{
public:
  DataBaseColumn(type::ColumnType columnType = type::UNDEFINED_COLUMN,
                 type::UnitType unitType = type::UNDEFINED_UNIT,
                 type::ValueType valueType = type::UNDEFINED_VALUE,
                 bool isRequired = false)
    : _columnType(columnType), _valueType(valueType), _unitType(unitType), _isRequired(isRequired)
  {
  }

  type::ColumnType getColumnType() const
  {
    return _columnType;
  }

  type::ValueType getValueType() const
  {
    return _valueType;
  }

  type::UnitType getUnitType() const
  {
    return _unitType;
  }

  bool isColumnRequired() const
  {
    return _isRequired;
  }

private:
  const type::ColumnType _columnType;
  const type::ValueType _valueType;
  const type::UnitType _unitType;
  const bool _isRequired;
};

}
