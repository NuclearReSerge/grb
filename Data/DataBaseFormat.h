#include "Common/Global.h"

#include <vector>

#pragma once

namespace grb
{

class DataType;

class DataBaseFormat
{
public:
  DataBaseFormat() = delete;
  DataBaseFormat(const type::DatabaseTableType dbType);
  virtual ~DataBaseFormat();

  type::DatabaseTableType getType() const;
  const type::ColumnFlags& getRequiredColumns() const;

  bool empty() const;
  std::size_t size() const;
  std::vector<DataType*>::const_iterator begin() const;
  std::vector<DataType*>::const_iterator end() const;
  const DataType& operator[](std::size_t index) const;

protected:
  friend class DataBaseFormatFactoryType;
  virtual void initialize() = 0;
  void addDataType(DataType* dataType);
  void setColumnFlag(std::size_t column, bool required = true);
  void setColumnFlags();

private:
  const type::DatabaseTableType _type;
  type::ColumnFlags _requiredFlags;
  std::vector<DataType*> _format;
};

}
