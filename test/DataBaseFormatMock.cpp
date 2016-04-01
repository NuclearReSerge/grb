#include "DataBaseFormatMock.h"

namespace grb
{
namespace test
{

DataBaseFormatMock::DataBaseFormatMock(const type::DatabaseTableType dbType)
  : DataBaseFormat(dbType)
{
}

void
DataBaseFormatMock::doInit()
{

}

std::vector<DataType*>&
DataBaseFormatMock::getFormatVector()
{
  return _format;
}


}
}
