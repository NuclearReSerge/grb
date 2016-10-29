#include "Data/DataBaseFormatMapper.h"
#include "Data/DataBaseColumn.h"

#include <vector>

#pragma once

namespace grb
{

class DataBaseFormat
{
public:
  DataBaseFormat(type::DataBaseFormatType dbType = type::UNDEFINED_DATABASE_FORMAT)
    : _type(dbType)
  {
  }

  virtual ~DataBaseFormat()
  {
    for (DataBaseColumn* item : _format)
    {
      delete item;
    }
    _format.clear();
  }

  type::DataBaseFormatType getType() const
  {
    return _type;
  }

  const type::ColumnFlags& getRequiredColumns() const
  {
    return _requiredFlags;
  }

  const std::vector<DataBaseColumn*>& getDataTypes() const
  {
    return _format;
  }

  std::vector<DataBaseColumn*>& getDataTypes()
  {
    return _format;
  }

  virtual void initialize() = 0;

protected:
  void addColumn(DataBaseColumn* dataType)
  {
    _format.push_back(dataType);
  }

  void setColumnFlag(std::size_t column, bool required = true)
  {
    _requiredFlags.set(column, required);
  }

  void setColumnFlags()
  {
    for (const DataBaseColumn* item : _format)
    {
      _requiredFlags.set(item->getColumnType(), item->isColumnRequired());
    }
  }

private:
  const type::DataBaseFormatType _type;
  type::ColumnFlags _requiredFlags;
  std::vector<DataBaseColumn*> _format;
};

}
