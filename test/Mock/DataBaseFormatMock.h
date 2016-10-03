#include "Data/DataBaseFormat.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class DataBaseFormatMock : public DataBaseFormat
{
public:
  DataBaseFormatMock(const type::DataBaseFormatType dbType)
    : DataBaseFormat(dbType)
  {
  }

  void addColumn(DataBaseColumn* dataType) { DataBaseFormat::addColumn(dataType); }
  void setColumnFlag(std::size_t column, bool required = true)
  {
    DataBaseFormat::setColumnFlag(column, required);
  }
  void setColumnFlags() { DataBaseFormat::setColumnFlags(); }

  MOCK_METHOD0(initialize, void());
};

} // namespace grb
