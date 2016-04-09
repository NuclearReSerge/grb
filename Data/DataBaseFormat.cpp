#include "Data/DataBaseFormat.h"

#include "Common/Global.h"
#include "Common/GlobalName.h"

#include <sstream>

namespace grb
{

DataBaseFormat::DataBaseFormat(const type::DatabaseTableType dbType)
  : _coordSys(type::COORDINATE_SYSTEM_UNDEFINED), _type(dbType)
{
}

DataBaseFormat::~DataBaseFormat()
{
  for (DataType* item : _format)
  {
    delete item;
  }
  _format.clear();
}

void
DataBaseFormat::initialize() throw(Exception)
{
  std::stringstream ss;
  ss << "Database format of type=" << _type << "[" << GlobalName::getDatabaseTable(_type)
     << "] was not initialized.";
  Exception exc(ss.str(), PRETTY_FUNCTION);
  throw exc;
}

type::DatabaseTableType
DataBaseFormat::getType() const
{
  return _type;
}

type::CoordinateSystemType
DataBaseFormat::getCoordinateSystem() const
{
  return _coordSys;
}

std::size_t
DataBaseFormat::getSize() const
{
  return _format.size();
}

const type::ColumnFlags&
DataBaseFormat::getRequiredColumns() const
{
  return _requiredFlags;
}

const DataType&
DataBaseFormat::getColumnFormat(std::size_t column) const throw(Exception)
{
  if (column >= _format.size())
  {
    std::stringstream ss;
    ss << "Column format of type=" << column << "["
       << GlobalName::getColumn((type::ColumnType) column) << "] does not exist.";
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  return *_format[column];
}

void
DataBaseFormat::setupRequiredColumns()
{
  for (const DataType* item : _format)
  {
    _requiredFlags.set(item->getColumnType(), item->isColumnRequired());
  }
}

}
