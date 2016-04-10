#include "Tools/Parser.h"

#include "Common/GlobalName.h"
#include "Data/Catalog.h"
#include "Data/CatalogEntry.h"
#include "Data/DataBaseFormat.h"
#include "Data/DataType.h"
#include "Tools/NameMapper.h"

#include <sstream>
#include <fstream>

namespace grb
{

namespace
{
const char* WHITESPACE   = " \t";
const char  COMMENT      = '#';
const char  DELIM_COLUMN = '|';
const char  DELIM_LIST   = ',';
const char  DELIM_RANGE  = '-';
}

Parser::Parser(const std::string& filename, const DataBaseFormat& format, Catalog& catalog)
  : _isSourceFile(false), _stream(nullptr), _row(0), _column(0),
    _columnType(type::COLUMN_TYPE_UNDEFINED), _format(format),
    _columnsRequired(_format.getRequiredColumns()), _catalog(catalog)
{
  openFileStream(filename);
}

Parser::Parser(std::istream* stream, const DataBaseFormat& format, Catalog& catalog)
  : _isSourceFile(false), _stream(stream), _row(0), _column(0),
    _columnType(type::COLUMN_TYPE_UNDEFINED), _format(format),
    _columnsRequired(_format.getRequiredColumns()), _catalog(catalog)
{
  if (!_stream)
  {
    Exception exc("Parsing failed, stream is nullptr", PRETTY_FUNCTION);
    throw exc;
  }
}

Parser::~Parser()
{
  if (_isSourceFile)
  {
    static_cast<std::ifstream*>(_stream)->close();
    delete _stream;
  }
}

void
Parser::openFileStream(const std::string& filename)
{
  _stream = new std::ifstream(filename);
  if(_stream->fail())
  {
    std::stringstream ss;
    ss << "Parsing failed, unable to open file=" << filename;
    Exception exc(ss.str(), PRETTY_FUNCTION);
    delete _stream;
    _stream = nullptr;
    throw exc;
  }
  _isSourceFile = true;
}

std::size_t
Parser::parse() throw(Exception)
{
  _row = 0;
  for (std::string line; std::getline(*_stream, line);)
  {
    if (line.empty() || line[0] == COMMENT)
      continue;

    CatalogEntry* entry = _catalog.createEntry();
    type::ColumnFlags columnFlags;
    std::stringstream ss(line);
    _column = 0;
    for (std::string element; std::getline(ss, element, DELIM_COLUMN);)
    {
      _columnType = _format.getColumnFormat(_column).getColumnType();

      element.erase(0, element.find_first_not_of(WHITESPACE));
      element.erase(element.find_last_not_of(WHITESPACE) + 1);
      try
      {
        columnFlags.set(_columnType, parseMapper(element, entry));
      }
      catch (Exception& exc)
      {
        columnFlags.set(_columnType, false);
        if (_columnsRequired.test(_columnType))
        {
          delete entry;
          throw;
        }
      }
      ++_column;
    }

    if (checkRequiredColumns(columnFlags))
    {
      delete entry;

      std::stringstream ss;
      ss << "Parsing failed at row=" << _row+1 << " columns={";
      for (std::size_t i = 0; i < columnFlags.size(); ++i)
      {
        if (columnFlags[i])
          ss << i << " [" << GlobalName::getColumn((type::ColumnType) i) << "] ";
      }
      ss << "} require valid values.";
      Exception exc(ss.str(), PRETTY_FUNCTION);
      throw exc;
    }
    _catalog.addEntry(entry);
    ++_row;
  }

  if (_row == 0 || _catalog.isEmpty())
  {
    Exception exc("Parsing failed, stream is empty", PRETTY_FUNCTION);
    throw exc;
  }
  return _row;
}

bool
Parser::checkRequiredColumns(type::ColumnFlags& columnFlags)
{
  columnFlags = (columnFlags & _columnsRequired) ^ _columnsRequired;
  return columnFlags.any();
}

bool
Parser::parseMapper(const std::string& raw, CatalogEntry* entry)
{
  type::ValueType valueType = _format.getColumnFormat(_column).getValueType();

  switch (valueType)
  {
    case type::FLAG:
      return parseValue(raw, entry->getFlag(_columnType));
    case type::INTEGER:
      return parseValue(raw, entry->getInteger(_columnType));
    case type::INDEX:
      return parseValue(raw, entry->getMapper(_columnType), entry->getIndex(_columnType));
    case type::INTEGER_RANGE:
      return parseValue(raw, entry->getIntegerRange(_columnType));
    case type::INDEX_LIST:
      return parseValue(raw, entry->getMapper(_columnType), entry->getIndexList(_columnType));
    case type::FLOAT:
      return parseValue(raw, entry->getFloat(_columnType));
    case type::STRING:
      return parseValue(raw, entry->getString(_columnType));
    case type::STRING_LIST:
      return parseValue(raw, entry->getStringList(_columnType));
    default:
      break;
  }

  std::stringstream ss;
  ss << "Parsing failed at row=" << _row+1 << ", column="<< _column+1
     << " [" << GlobalName::getColumn(_columnType) << "] value type="
     << valueType << " [" << GlobalName::getValue(valueType) << "] is not supported.";
  Exception exc(ss.str(), PRETTY_FUNCTION);
  throw exc;
}

bool
Parser::parseValue(const std::string& raw, type::Flag* value)
{ 
  if (!value)
    throwException(type::FLAG);

  switch (raw[0])
  {
    case 'N':
    {
      *value = false;
      return true;
    }
    case 'Y':
    {
      *value = true;
      return true;
    }
    default:
      break;
  }
  std::stringstream ss;
  ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
     << " [" << GlobalName::getColumn(_columnType) << "] for bool=" << raw;
  Exception exc(ss.str(), PRETTY_FUNCTION);
  throw exc;
}

bool
Parser::parseValue(const std::string& raw, type::Integer* value)
{
  if (!value)
    throwException(type::INTEGER);

  try
  {
    long res = std::stol(raw);
    if (res < 0)
    {
      return false;
    }
    *value = (std::size_t) res;
  }
  catch (std::exception& sysExc)
  {
    std::stringstream ss;
    ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
       << " [" << GlobalName::getColumn(_columnType) << "] for int=" << raw
       << ", exc.what()=" << sysExc.what();
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
Parser::parseValue(const std::string& raw, const NameMapper* mapper, type::Index* value)
{
  if (!mapper || !value)
    throwException(type::INDEX);

  try
  {
    *value = mapper->getIndex(raw);
  }
  catch (Exception& mapExc)
  {
    std::stringstream ss;
    ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
       << " [" << GlobalName::getColumn(_columnType) << "] for string=" << raw << " and mapper="
       << mapper->getColumnType() << " [" << GlobalName::getColumn(mapper->getColumnType())
       << "], mapperExc.what()\n" << mapExc.what();
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
Parser::parseValue(const std::string& raw, type::IntegerRange* value)
{
  if (!value)
    throwException(type::INTEGER_RANGE);

  std::stringstream ss(raw);
  for (std::string item; std::getline(ss, item, DELIM_RANGE);)
  {
    type::Integer val;
    if (parseValue(item, &val))
    {
      value->push_back(val);
    }
  }

  if (value->size() != 2)
  {
    std::stringstream ss;
    ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
       << " [" << GlobalName::getColumn(_columnType) << "] for int[2]=" << raw;
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
Parser::parseValue(const std::string& raw, const NameMapper* mapper, type::IndexList* valueList)
{
  if (!valueList)
    throwException(type::INDEX_LIST);

  std::stringstream ss(raw);
  for (std::string item; std::getline(ss, item, DELIM_LIST);)
  {
    int index;
    if (!parseValue(item, mapper, &index))
    {
      return false;
    }
    valueList->push_back(index);
  }

  if (valueList->empty())
  {
    std::stringstream ss;
    ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
       << " [" << GlobalName::getColumn(_columnType) << "] for index_list=" << raw
       << " is empty";
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
Parser::parseValue(const std::string& raw, type::Float* value)
{
  if (!value)
    throwException(type::FLOAT);

  try
  {
    *value = std::stod(raw);
  }
  catch (std::exception& sysExc)
  {
    std::stringstream ss;
    ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
       << " [" << GlobalName::getColumn(_columnType) << "] for double=" << raw
       << ", exc.what()=" << sysExc.what();
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
Parser::parseValue(const std::string& raw, type::String* value)
{
  if (!value)
    throwException(type::STRING);

  *value = raw;
  return !value->empty();
}

bool
Parser::parseValue(const std::string& raw, type::StringList* valueList)
{
  if (!valueList)
    throwException(type::STRING_LIST);

  std::stringstream ss(raw);
  for (std::string item; std::getline(ss, item, DELIM_LIST);)
  {
    if (item.empty())
      return false;
    valueList->push_back(item);
  }

  return !valueList->empty();
}

void
Parser::throwException(type::ValueType valueType)
{
  std::stringstream ss;
  ss << "Parsing failed at row=" << _row+1 << ", column="<< _column+1
     << " [" << GlobalName::getColumn(_columnType) << "] value type="
     << valueType << " [" << GlobalName::getValue(valueType) << "] does not match the column.";
  Exception exc(ss.str(), PRETTY_FUNCTION);
  throw exc;
}

}
