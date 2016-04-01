#include "Data/DataBaseFormat.h"

#pragma once

namespace grb
{
namespace test
{

class DataBaseFormatMock : public DataBaseFormat
{
public:
  DataBaseFormatMock() = delete;
  DataBaseFormatMock(const type::DatabaseTableType dbType);

  std::vector<DataType*>& getFormatVector();

protected:
  void doInit();


};

}
}
