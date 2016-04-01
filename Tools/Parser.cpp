#include "Common/Global.h"
#include "Data/DataBaseFormat.h"
#include "Data/Observatory.h"
#include "Data/Reference.h"
#include "Data/Region.h"
#include "Data/TimeDef.h"
#include "Data/TimeMod.h"

#include "Tools/Parser.h"

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
    CatalogEntry entry;
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
Parser::parseMapper(const std::string& raw, CatalogEntry& entry)
{
  type::ValueType valueType = _format->getColumnFormat(_column).getValueType();

  switch (valueType)
  {
    case type::FLAG:
      return parseValue(raw, mapFlag(entry));
    case type::INTEGER:
      return parseValue(raw, mapInteger(entry));
    case type::INDEX:
      return parseValue(raw, mapIndex(entry));
    case type::INTEGER_RANGE:
      return parseValue(raw, mapIntegerRange(entry));
    case type::INDEX_LIST:
      return parseValue(raw, mapIndexList(entry));
    case type::FLOAT:
      return parseValue(raw, mapFloat(entry));
    case type::TIMEPOINT:
      return parseValue(raw, mapTimePoint(entry));
    case type::COORDINATE:
      return parseValue(raw, mapFloat(entry));
    case type::STRING:
      return parseValue(raw, mapString(entry));
    case type::STRING_LIST:
      return parseValue(raw, mapStringList(entry));
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

type::Flag*
Parser::mapFlag(CatalogEntry& entry)
{
  switch (_column)
  {
    case type::AFTERGLOW_FLAG:
      return &entry.afterglow_flag;
    case type::FLUX_FLAG:
      return &entry.flux_flag;
    default:
      break;
  }
  throwException(type::FLAG);
  return nullptr;
}

type::Integer*
Parser::mapInteger(CatalogEntry& entry)
{
  switch (_column)
  {
    case type::RECORD_NUMBER:
      return &entry.record_number;
    case type::ID:
      return &entry.id;
    case type::T50_EMIN:
      return &entry.t50.emin;
    case type::T50_EMAX:
      return &entry.t50.emax;
    case type::T90_EMIN:
      return &entry.t90.emin;
    case type::T90_EMAX:
      return &entry.t90.emax;
    case type::CLASS:
      return &entry.class_id;
    default:
      break;
  }
  throwException(type::INTEGER);
  return nullptr;
}

type::Index*
Parser::mapIndex(CatalogEntry& entry)
{
  switch (_column)
  {
    case type::TIME_DEF:
      return &entry.time_def;
    case type::OBSERVATORY:
      return &entry.observatory;
    case type::REGION:
      return &entry.region;
    case type::T50_MOD:
      return &entry.t50.mod;
    case type::T90_MOD:
      return &entry.t90.mod;
    default:
      break;
  }
  throwException(type::INDEX);
  return nullptr;
}

type::IntegerRange*
Parser::mapIntegerRange(CatalogEntry& entry)
{
  switch (_column)
  {
    case type::T50:
      return &entry.t50.range;
    case type::T90:
      return &entry.t90.range;
    default:
      break;
  }
  throwException(type::INTEGER_RANGE);
  return nullptr;
}

type::IndexList*
Parser::mapIndexList(CatalogEntry& entry)
{
  switch (_column)
  {
    case type::REFERENCE:
      return &entry.reference;
    default:
      break;
  }
  throwException(type::INDEX_LIST);
  return nullptr;
}

type::Float*
Parser::mapFloat(CatalogEntry& entry)
{
  switch (_column)
  {
    case type::COORD_RA:
      return &entry.coordinates.u.j2000.rightAscension;
    case type::COORD_DEC:
      return &entry.coordinates.u.j2000.declination;
    case type::COORD_FLAG:
      return &entry.coordinates.coord_flag;
    case type::T50:
      return &entry.t50.value;
    case type::T50_ERROR:
      return &entry.t50.error;
    case type::T90:
      return &entry.t90.value;
    case type::T90_ERROR:
      return &entry.t90.error;
    case type::T_OTHER:
      return &entry.t_other.value;
    default:
      break;
  }
  throwException(type::FLOAT);
  return nullptr;
}

type::TimePoint*
Parser::mapTimePoint(CatalogEntry& entry)
{
  switch (_column)
  {
    case type::TIME:
      return &entry.time;
    default:
      break;
  }
  throwException(type::TIMEPOINT);
  return nullptr;
}

type::String*
Parser::mapString(CatalogEntry& entry)
{
  switch (_column)
  {
    case type::NAME:
      return &entry.name;
    case type::NOTES:
      return &entry.t_other.notes;
    case type::FLUX_NOTES:
      return &entry.flux_notes;
    case type::LOCAL_NOTES:
      return &entry.local_notes;
    default:
      break;
  }
  throwException(type::STRING);
  return nullptr;
}

type::StringList*
Parser::mapStringList(CatalogEntry& entry)
{
  switch (_column)
  {
    case type::ALT_NAMES:
      return &entry.alt_names;
    default:
      break;
  }
  throwException(type::STRING_LIST);
  return nullptr;
}

NameMapper*
Parser::getMapper()
{
  switch (_column)
  {
    case type::OBSERVATORY:
      return Observatory::instance();
    case type::REFERENCE:
      return Reference::instance();
    case type::REGION:
      return Region::instance();
    case type::TIME_DEF:
      return TimeDef::instance();
    case type::T50_MOD:
      return Time50Mod::instance();
    case type::T90_MOD:
      return Time90Mod::instance();
    default:
      break;
  }
  std::stringstream ss;
  ss << "Parsing failed at row=" << _row+1 << ", column="<< _column+1
     << " [" << GlobalName::getColumn(_column) << "] unable to select a Name Mapper.";
  Exception exc(ss.str(), PRETTY_FUNCTION);
  throw exc;
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

bool
Parser::parseValue(const std::string& raw, type::Flag* value)
{
  if (raw.empty())
    return false;

  switch (raw[0])
  {
    case 'N':
    {
      *value = false;
      break;
    }
    case 'Y':
    {
      *value = true;
      break;
    }
    default:
    {
      std::stringstream ss;
      ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
         << " [" << GlobalName::getColumn(_column) << "] for bool=" << raw;
      Exception exc(ss.str(), PRETTY_FUNCTION);
      throw exc;
    }
  }
  return true;
}

bool
Parser::parseValue(const std::string& raw, type::Integer* value)
{
  if (raw.empty())
    return false;

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
Parser::parseValue(const std::string& raw, type::Index* value)
{
  NameMapper* mapper = getMapper();
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
Parser::parseValue(const std::string& raw, type::IndexList* valueList)
{
  std::stringstream ss(raw);
  for (std::string item; std::getline(ss, item, DELIM_LIST);)
  {
    int index;
    if (!parseValue(item, &index))
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
  if (raw.empty())
    return false;

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
  *value = std::move(raw);
  return !value->empty();
}

bool
Parser::parseValue(const std::string& raw, type::StringList* valueList)
{
  std::stringstream ss(raw);
  for (std::string item; std::getline(ss, item, DELIM_LIST);)
  {
    valueList->push_back(item);
  }
  return !valueList->empty();
}

}
