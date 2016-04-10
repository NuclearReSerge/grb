#include "Common/Global.h"

#pragma once

namespace grb
{

class DataType
{
public:
  DataType();
  DataType(type::ColumnType columnType, bool isRequired, type::UnitType unitType,
           type::ValueType valueType);

  type::ColumnType getColumnType() const;
  bool isColumnRequired() const;
  type::UnitType getUnitType() const;
  type::ValueType getValueType() const;

private:
  const type::ColumnType _columnType;
  const bool _isRequired;
  const type::UnitType _unitType;
  const type::ValueType _valueType;
};

}
