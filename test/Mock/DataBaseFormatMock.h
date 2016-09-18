#include "Data/DataBaseFormat.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class DataBaseFormatMock : public DataBaseFormat
{
public:
  DataBaseFormatMock(type::DatabaseFormatType dbType = type::UNDEFINED_DATABASE_FORMAT)
    : DataBaseFormat(dbType)
  {
  }

  MOCK_METHOD0(initialize, void());
};

} // namespace grb
