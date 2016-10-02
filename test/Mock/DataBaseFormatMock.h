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

  MOCK_METHOD0(initialize, void());
};

} // namespace grb
