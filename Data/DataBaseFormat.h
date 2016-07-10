#include "Data/DataBaseFormatMapper.h"
#include "Data/DataType.h"

#include <vector>

#pragma once

namespace grb
{

class DataBaseFormat
{
public:
  DataBaseFormat() = delete;
  DataBaseFormat(const type::DatabaseTableType dbType);
  virtual ~DataBaseFormat();

  type::DatabaseTableType getType() const;
  const type::ColumnFlags& getRequiredColumns() const;
  std::vector<DataType*>& getDataTypes();

  virtual void initialize() = 0;
protected:

  void addDataType(DataType* dataType);
  void setColumnFlag(std::size_t column, bool required = true);
  void setColumnFlags();

private:
  const type::DatabaseTableType _type;
  type::ColumnFlags _requiredFlags;
  std::vector<DataType*> _format;
};

}
