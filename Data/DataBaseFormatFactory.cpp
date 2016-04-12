#include "Data/DataBaseFormatFactory.h"

#include "Common/GlobalName.h"
#include "Data/DataBaseFormatGrbcat.h"

#include <sstream>

namespace grb
{

DataBaseFormatFactoryType::DataBaseFormatFactoryType()
{
  initialize();
}

DataBaseFormatFactoryType::~DataBaseFormatFactoryType()
{
  for (const auto& format : _formatMap)
  {
    delete format.second;
  }
}

const DataBaseFormat&
DataBaseFormatFactoryType::getFormat(const type::DatabaseTableType dbType) throw(Exception)
{
  try
  {
    return *_formatMap.at(dbType);
  }
  catch (std::out_of_range& sysExc)
  {
    std::stringstream ss;
    ss << "Database format of type=" << dbType << "[" << GlobalName::getDatabaseTable(dbType)
       << "] does not exist, exc.what()=" << sysExc.what();
    Exception exc(type::EXCEPTION_CRITICAL, ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
}

void
DataBaseFormatFactoryType::initialize()
{
  _formatMap.insert({type::HEASARC_GRBCAT, new DataBaseFormatGrbcat});

  for (const auto& format : _formatMap)
  {
    format.second->initialize();
  }
}

}
