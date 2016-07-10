#include "Data/ColumnMapper.h"
#include "Data/UnitMapper.h"
#include "Data/ValueMapper.h"

#include <bitset>
#include <vector>

#pragma once

namespace grb
{

namespace type
{

typedef std::bitset<type::UNDEFINED_COLUMN> ColumnFlags;

}

class DataType
{
public:
  DataType();
  DataType(type::ColumnType columnType, bool isRequired, type::UnitType unitType,
           type::ValueType valueType);

  type::ColumnType getColumnType() const;
  type::ValueType getValueType() const;
  type::UnitType getUnitType() const;
  bool isColumnRequired() const;

private:
  const type::ColumnType _columnType;
  const type::ValueType _valueType;
  const type::UnitType _unitType;
  const bool _isRequired;
};

}
