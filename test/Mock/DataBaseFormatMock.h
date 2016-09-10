#include "Data/DataBaseFormat.h"

#pragma once

namespace grb
{

class DataBaseFormatMock : public DataBaseFormat
{
public:
  DataBaseFormatMock()
    : DataBaseFormat(type::TEST_DATABASE_TABLE)
  {
  }

  void setColumnFlag(std::size_t column, bool required = true)
  {
    DataBaseFormat::setColumnFlag(column, required);
  }

  void initialize();
};

} // namespace grb
