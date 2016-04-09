#include "Common/Exception.h"
#include "Data/DataType.h"

#pragma once

namespace grb
{

class DataBaseFormat
{
public:
  DataBaseFormat() = delete;
  DataBaseFormat(const type::DatabaseTableType dbType);
  virtual ~DataBaseFormat();

  virtual void initialize() throw(Exception);
  type::DatabaseTableType getType() const;
  type::CoordinateSystemType getCoordinateSystem() const;
  std::size_t getSize() const;
  const type::ColumnFlags& getRequiredColumns() const;
  const DataType& getColumnFormat(const std::size_t column) const throw(Exception);

protected:
  void setupRequiredColumns();

  type::CoordinateSystemType _coordSys;
  std::vector<DataType*> _format;
  const type::DatabaseTableType _type;
  type::ColumnFlags _requiredFlags;
};

}
