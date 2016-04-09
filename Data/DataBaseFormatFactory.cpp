#include "Data/DataBaseFormatFactory.h"

#include "Common/GlobalName.h"
#include "DataBaseFormatGrbcat.h"

#include <sstream>

namespace grb
{

DataBaseFormatFactoryType::DataBaseFormatFactoryType()
{
  _HEASARC_GRBCAT = new DataBaseFormatGrbcat();
}

const DataBaseFormat*
DataBaseFormatFactoryType::getFormat(const type::DatabaseTableType dbType) throw(Exception)
{
  switch (dbType)
  {
    case type::HEASARC_GRBCAT:
    {
      return _HEASARC_GRBCAT;
    }
    default:
    {
      std::stringstream ss;
      ss << "Database format of type=" << dbType << "[" << GlobalName::getDatabaseTable(dbType)
         << "] does not exist.";
      Exception exc(ss.str(), PRETTY_FUNCTION);
      throw exc;
    }
  }
}

}
