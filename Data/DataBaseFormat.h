#include "Data/DataBaseFormatMapper.h"
#include "Data/DataBaseColumn.h"

#include <vector>

#pragma once

namespace grb
{

class DataBaseFormat
{
public:
  DataBaseFormat() = delete;
  DataBaseFormat(const type::DatabaseFormatType dbType = type::UNDEFINED_DATABASE_TABLE)
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

  type::DatabaseFormatType getType() const
  {
    return _type;
  }

  const type::ColumnFlags& getRequiredColumns() const
  {
    return _requiredFlags;
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
  const type::DatabaseFormatType _type;
  type::ColumnFlags _requiredFlags;
  std::vector<DataBaseColumn*> _format;
};

}
