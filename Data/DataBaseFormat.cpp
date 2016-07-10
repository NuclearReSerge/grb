#include "Data/DataBaseFormat.h"

#include "Common/Exception.h"

#include <sstream>

namespace grb
{

DataBaseFormat::DataBaseFormat(const type::DatabaseTableType type)
  : _type(type)
{
}

DataBaseFormat::~DataBaseFormat()
{
  for (DataType* item : _format)
  {
    delete item;
  }
  _format.clear();
}

type::DatabaseTableType
DataBaseFormat::getType() const
{
  return _type;
}

const type::ColumnFlags&
DataBaseFormat::getRequiredColumns() const
{
  return _requiredFlags;
}

std::vector<DataType*>&
DataBaseFormat::getDataTypes()
{
  return _format;
}

void
DataBaseFormat::addDataType(DataType* dataType)
{
  _format.push_back(dataType);
}

void
DataBaseFormat::setColumnFlag(std::size_t column, bool required)
{
  _requiredFlags.set(column, required);
}

void
DataBaseFormat::setColumnFlags()
{
  for (const DataType* item : _format)
  {
    _requiredFlags.set(item->getColumnType(), item->isColumnRequired());
  }
}

}
