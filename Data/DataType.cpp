#include "Data/DataType.h"

namespace grb
{
DataType::DataType()
  : _columnType(type::COLUMN_TYPE_UNDEFINED), _isRequired(false),
    _unitType(type::UNIT_TYPE_UNDEFINED), _valueType(type::VALUE_TYPE_UNDEFINED)
{
}

DataType::DataType(type::ColumnType columnType, bool isRequired, type::UnitType unitType,
                   type::ValueType valueType)
  : _columnType(columnType), _isRequired(isRequired), _unitType(unitType), _valueType(valueType)
{
}

type::ColumnType
DataType::getColumnType() const
{
  return _columnType;
}

bool
DataType::isColumnRequired() const
{
  return _isRequired;
}

type::UnitType
DataType::getUnitType() const
{
  return _unitType;
}

type::ValueType
DataType::getValueType() const
{
  return _valueType;
}

}
