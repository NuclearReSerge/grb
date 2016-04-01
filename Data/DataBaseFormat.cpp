#include "Common/Global.h"

#include "Data/DataBaseFormat.h"

#include <sstream>
namespace grb
{

DataBaseFormat::DataBaseFormat(const type::DatabaseTableType dbType)
  : _type(dbType)
{
  switch (_type)
  {
    case type::HEASARC_GRBCAT:
    {
      initHEASARC_GRBCAT();
      break;
    }
    default:
    {
      std::stringstream ss;
      ss << "Database format of type=" << dbType << "[" << GlobalName::getDatabaseTable(dbType)
         << "] was not initialized.";
      Exception exc(ss.str());
      throw exc;
    }
  }

  for (DataType* item : _format)
  {
    _requiredFlags[item->getColumnType(), item->isColumnRequired()];
  }
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

const DataType&
DataBaseFormat::getColumnFormat(std::size_t column) const throw(Exception)
{

  if (column >= _format.size())
  {
    std::stringstream ss;
    ss << "Column format of type=" << column << "["
       << GlobalName::getColumn((type::ColumnType) column) << "] does not exist.";
    Exception exc(ss.str());
    throw exc;
  }
  return *_format[column];
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

void
DataBaseFormat::initHEASARC_GRBCAT()
{
  _format.push_back(new DataType(type::RECORD_NUMBER,  true,  type::NO_UNIT, type::INTEGER));
  _format.push_back(new DataType(type::ID,             true,  type::NO_UNIT, type::INTEGER));
  _format.push_back(new DataType(type::NAME,           true,  type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::ALT_NAMES,      false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::TIME,           true,  type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::TIME_DEF,       true,  type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::OBSERVATORY,    true,  type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::COORD_RA,       false, type::DEGREE,  type::STRING));
  _format.push_back(new DataType(type::COORD_DEC,      false, type::DEGREE,  type::STRING));
  _format.push_back(new DataType(type::COORD_FLAG,     true,  type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::REGION,         false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::AFTERGLOW_FLAG, true,  type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::REFERENCE,      true,  type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::T50_MOD,        false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::T50,            false, type::SECOND,  type::FLOAT));
  _format.push_back(new DataType(type::T50_ERROR,      false, type::SECOND,  type::FLOAT));
  _format.push_back(new DataType(type::T50_RANGE,      false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::T50_EMIN,       false, type::KILO_EV, type::INTEGER));
  _format.push_back(new DataType(type::T50_EMAX,       false, type::KILO_EV, type::INTEGER));
  _format.push_back(new DataType(type::T90_MOD,        false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::T90,            false, type::SECOND,  type::FLOAT));
  _format.push_back(new DataType(type::T90_ERROR,      false, type::SECOND,  type::FLOAT));
  _format.push_back(new DataType(type::T90_RANGE,      false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::T90_EMIN,       false, type::KILO_EV, type::INTEGER));
  _format.push_back(new DataType(type::T90_EMAX,       false, type::KILO_EV, type::INTEGER));
  _format.push_back(new DataType(type::T_OTHER,        false, type::SECOND,  type::FLOAT));
  _format.push_back(new DataType(type::FLUX_FLAG,      true,  type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::NOTES,          false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::FLUX_NOTES,     false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::LOCAL_NOTES,    false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::CLASS,          false, type::NO_UNIT, type::STRING));
}

DataBaseFormatFactory::DataBaseFormatFactory()
  : _HEASARC_GRBCAT(type::HEASARC_GRBCAT)
{
}

const DataBaseFormat&
DataBaseFormatFactory::getFormat(const type::DatabaseTableType dbType) throw(Exception)
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
      Exception exc(ss.str());
      throw exc;
    }
  }
}

}
