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

  void initialize() throw(Exception);

  std::vector<DataType*>& getFormatVector();
  void setCoordinateSystem(type::CoordinateSystemType coordSys);
  void setColumnRequired(std::size_t pos, bool val);

};

}
}
