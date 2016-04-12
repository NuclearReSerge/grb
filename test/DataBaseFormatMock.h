#include "Data/DataBaseFormat.h"

#pragma once

namespace grb
{
namespace test
{

class DataBaseFormatMock : public DataBaseFormat
{
public:
  DataBaseFormatMock();
  void initialize();

  void setColumnFlag(std::size_t column, bool required = true);

};

}
}
