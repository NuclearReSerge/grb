#include "Data/DataBaseFormat.h"

#include "Common/Exception.h"
#include "Common/GlobalName.h"
#include "Data/DataType.h"

#include <sstream>

namespace grb
{

DataBaseFormat::DataBaseFormat(const type::DatabaseTableType dbType)
  : _type(dbType)
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

type::DatabaseTableType
DataBaseFormat::getType() const
{
  return _type;
}

const type::ColumnFlags&
DataBaseFormat::getRequiredColumns() const
{
  return _requiredFlags;
}


bool
DataBaseFormat::empty() const
{
  return _format.empty();
}

std::size_t
DataBaseFormat::size() const
{
  return _format.size();
}

std::vector<DataType*>::const_iterator
DataBaseFormat::begin() const
{
  return _format.begin();
}

std::vector<DataType*>::const_iterator
DataBaseFormat::end() const
{
  return _format.end();
}

const DataType&
DataBaseFormat::operator[](std::size_t index) const
{
  if (index < _format.size())
    return *_format[index];

  std::stringstream ss;
  ss << "Database format type=" << _type << " [" << GlobalName::getDatabaseTable(_type)
     << "]. Index=" << index << " is out of range.";
  Exception exc(type::EXCEPTION_CRITICAL, ss.str(), PRETTY_FUNCTION);
  throw exc;
}

void
DataBaseFormat::addDataType(DataType* dataType)
{
  _format.push_back(dataType);
}

void
DataBaseFormat::setColumnFlag(std::size_t column, bool required)
{
  _requiredFlags.set(column, required);
}

void
DataBaseFormat::setColumnFlags()
{
  for (const DataType* item : _format)
  {
    _requiredFlags.set(item->getColumnType(), item->isColumnRequired());
  }
}

}
