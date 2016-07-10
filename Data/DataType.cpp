#include "Data/DataType.h"

namespace grb
{

static std::vector<std::pair<std::string, std::string>> COLUMN_NAMES
{

};

DataType::DataType()
  : _columnType(type::UNDEFINED_COLUMN), _valueType(type::UNDEFINED_VALUE),
    _unitType(type::UNDEFINED_UNIT), _isRequired(false)
{
}

DataType::DataType(type::ColumnType columnType, bool isRequired, type::UnitType unitType,
                   type::ValueType valueType)
  : _columnType(columnType), _valueType(valueType), _unitType(unitType), _isRequired(isRequired)
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
