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
  DataBaseColumn()
    : _columnType(type::UNDEFINED_COLUMN), _valueType(type::UNDEFINED_VALUE),
      _unitType(type::UNDEFINED_UNIT), _isRequired(false)
  {
  }

  DataBaseColumn(type::ColumnType columnType, bool isRequired, type::UnitType unitType,
           type::ValueType valueType)
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
