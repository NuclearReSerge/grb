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

  std::vector<DataType*>& getFormatVector();
  void setCoordinateSystem(type::CoordinateSystemType coordSys);
  void resetRequiredColumns();

protected:
  void initializeTest();
};

}
}
