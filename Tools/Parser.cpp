#include "Tools/Parser.h"

#include "Common/Global.h"
#include "Common/GlobalName.h"
#include "Data/CatalogEntry.h"
#include "Data/CatalogEntryFactory.h"
#include "Data/DataBaseFormat.h"


#include <iostream>
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

Parser::Parser(const std::string& filename, const DataBaseFormat* format, Catalog* catalog)
  : _format(format), _catalog(catalog)
{
  openFileStream(filename);
}

Parser::Parser(std::istream* stream, const DataBaseFormat* format, Catalog* catalog)
  : _stream(stream), _format(format), _catalog(catalog)
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
  const type::ColumnFlags& columnFlagsRequired = _format->getRequiredColumns();

  _row = 0;
  for (std::string line; std::getline(*_stream, line);)
  {
    if (line[0] == COMMENT)
      continue;

    type::ColumnFlags columnFlags;
    CatalogEntry* entry = CatalogEntryFactory::instance()->create(_catalog->getType());

    std::stringstream ss(line);
    std::size_t col = 0;
    std::cout << "COLUMNS REQUIRED: " << columnFlagsRequired << std::endl;

    for (std::string element; std::getline(ss, element, DELIM_COLUMN);)
    {
      _column = _format->getColumnFormat(col++).getColumnType();

      element.erase(0, element.find_first_not_of(WHITESPACE));
      element.erase(element.find_last_not_of(WHITESPACE) + 1);
      std::cout << "item[" << _column <<", " << GlobalName::getColumn(_column) << "]="
                << element << ""<< std::endl;
      try
      {
        columnFlags.set(_column, parseMapper(element, entry));
      }
      catch (Exception& exc)
      {
        delete entry;
        std::cout << exc.what() << std::endl;
        columnFlags.set(_column, false);
        if (columnFlagsRequired.test(_column))
        {
          std::cout << "COLUMN REQUIRED" << std::endl;
          throw;
        }
      }
    }

    columnFlags = (columnFlags & columnFlagsRequired) ^ columnFlagsRequired;
    if (columnFlags.any())
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
    _catalog->get().push_back(entry);
    ++_row;
  }

  if (_row == 0 || _catalog->get().empty())
  {
    Exception exc("Parsing failed, stream is empty", PRETTY_FUNCTION);
    throw exc;
  }
  return _row;
}

bool
Parser::parseMapper(const std::string& raw, CatalogEntry* entry)
{
  type::ValueType valueType = _format->getColumnFormat(_column).getValueType();

  switch (valueType)
  {
    case type::FLAG:
      return parseValue(raw, entry->getFlag(_column));
    case type::INTEGER:
      return parseValue(raw, entry->getInteger(_column));
    case type::INDEX:
      return parseValue(raw, entry->getMapper(_column), entry->getIndex(_column));
    case type::INTEGER_RANGE:
      return parseValue(raw, entry->getIntegerRange(_column));
    case type::INDEX_LIST:
      return parseValue(raw, entry->getMapper(_column), entry->getIndexList(_column));
    case type::FLOAT:
      return parseValue(raw, entry->getFloat(_column));
    case type::TIMEPOINT:
      return parseValue(raw, entry->getTimePoint(_column));
    case type::COORDINATE:
      return parseValue(raw, entry->getFloat(_column));
    case type::STRING:
      return parseValue(raw, entry->getString(_column));
    case type::STRING_LIST:
      return parseValue(raw, entry->getStringList(_column));
    default:
      break;
  }

  std::stringstream ss;
  ss << "Parsing failed at row=" << _row+1 << ", column="<< _column+1
     << " [" << GlobalName::getColumn(_column) << "] value type="
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
     << " [" << GlobalName::getColumn(_column) << "] for bool=" << raw;
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
    int res = std::stoi(raw);
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
       << " [" << GlobalName::getColumn(_column) << "] for int=" << raw
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
       << " [" << GlobalName::getColumn(_column) << "] for string=" << raw << " and mapper="
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

  int i = 0;
  std::stringstream ss(raw);
  for (std::string item; std::getline(ss, item, DELIM_RANGE);)
  {
    if (!parseValue(item, value + i++))
      return false;
  }
  if (i != 2)
  {
    std::stringstream ss;
    ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
       << " [" << GlobalName::getColumn(_column) << "] for int[2]=" << raw;
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
  return !valueList->empty();
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
       << " [" << GlobalName::getColumn(_column) << "] for double=" << raw
       << ", exc.what()=" << sysExc.what();
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
Parser::parseValue(const std::string& raw, type::TimePoint* value)
{
  if (!value)
    throwException(type::TIMEPOINT);


  if (raw.empty())
  {
    return false;
  }

  *value = std::chrono::system_clock::now();
  return true;
}

bool
Parser::parseValue(const std::string& raw, type::String* value)
{
  if (!value)
    throwException(type::STRING);

  *value = std::move(raw);
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
    valueList->push_back(item);
  }
  return !valueList->empty();
}

void
Parser::throwException(type::ValueType valueType)
{
  std::stringstream ss;
  ss << "Parsing failed at row=" << _row+1 << ", column="<< _column+1
     << " [" << GlobalName::getColumn(_column) << "] value type="
     << valueType << " [" << GlobalName::getValue(valueType) << "] does not match the column.";
  Exception exc(ss.str(), PRETTY_FUNCTION);
  throw exc;
}

}
