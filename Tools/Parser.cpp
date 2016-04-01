#include "Common/Global.h"
#include "Data/DataBaseFormat.h"
#include "Data/Observatory.h"
#include "Data/Reference.h"
#include "Data/Region.h"
#include "Data/TimeDef.h"
#include "Data/TimeMod.h"

#include "Tools/Parser.h"

#include <sstream>
#include <fstream>

namespace grb
{

namespace
{
const char* WHITESPACE = " \t";
const char COMMENT = '#';
const char EMPTY_ELEMENT = '#';
const char DELIM_COLUMN = '|';
const char DELIM_LIST = ',';
const char DELIM_RANGE = '-';


}

Parser::Parser(const std::string& filename)
{
  openFileStream(filename);
}

Parser::Parser(std::istream* stream)
  : _stream(stream)
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
Parser::openFileStream(const std::string& filename) throw(Exception)
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

std::size_t Parser::parse(const DataBaseFormat& format, Catalog& catalog) throw(Exception)
{

  _row = 0;
  for (std::string line; std::getline(*_stream, line);)
  {
    if (line[0] == COMMENT)
      continue;

    type::ColumnFlags columnFlags;
    CatalogEntry entry;
    std::stringstream ss(line);
    std::size_t col = 0;
    for (std::string element; std::getline(ss, element, DELIM_COLUMN);)
    {
      _column = (type::ColumnType) format.getColumnFormat(col).getColumnType();
      element.erase(0, element.find_first_not_of(WHITESPACE));
      element.erase(element.find_last_not_of(WHITESPACE) + 1);
      //std::cout << "item[" << _column << "]=|" << element << "|"<< std::endl;

      if (element.empty())
      {
        ++col;
        continue;
      }

      parseMapper(entry, columnFlags, element);
      ++col;
    }

    const type::ColumnFlags& columnFlagsRequired = format.getRequiredColumns();

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
    catalog.get().push_back(entry);
    ++_row;
  }

  if (_row == 0 || catalog.get().empty())
  {
    Exception exc("Parsing failed, stream is empty", PRETTY_FUNCTION);
    throw exc;
  }
  return _row;
}

void
Parser::parseMapper(CatalogEntry& entry, type::ColumnFlags& columnFlags,
                    const std::string& item) throw(Exception)
{
  switch (_column)
  {
    case type::NAME:
    {
      columnFlags.set(_column, parseString(item, entry.name));
      break;
    }
    case type::TIME:
    {
      columnFlags.set(_column, parseTimePoint(item, entry.time));
      break;
    }
    case type::OBSERVATORY:
    {
      columnFlags.set(_column, parseIndex(item, Observatory::instance(), entry.observatory));
      break;
    }
    case type::COORD_H:
    {
      columnFlags.set(_column, parseDouble(item, entry.coordinates.u.undefined.horizontal));
      break;
    }
    case type::COORD_V:
    {
      columnFlags.set(_column, parseDouble(item, entry.coordinates.u.undefined.vertical));
      break;
    }
    case type::COORD_FLAG:
    {
      columnFlags.set(_column, parseDouble(item, entry.coordinates.coord_flag));
      break;
    }
    case type::REGION:
    {
      columnFlags.set(_column, parseIndex(item, Region::instance(), entry.region));
      break;
    }
    case type::AFTERGLOW_FLAG:
    {
      columnFlags.set(_column, parseFlag(item, entry.afterglow_flag));
      break;
    }
    case type::FLUX_FLAG:
    {
      columnFlags.set(_column, parseFlag(item, entry.flux_flag));
      break;
    }
    case type::ID:
    {
      columnFlags.set(_column, parseInteger(item, entry.id));
      break;
    }
    case type::RECORD_NUMBER:
    {
      columnFlags.set(_column, parseInteger(item, entry.record_number));
      break;
    }
    case type::ALT_NAMES:
    {
      columnFlags.set(_column, parseVectorOfStrings(item, entry.alt_names));
      break;
    }
    case type::TIME_DEF:
    {
      columnFlags.set(_column, parseIndex(item, TimeDef::instance(), entry.time_def));
      break;
    }
    case type::REFERENCE:
    {
      columnFlags.set(_column, parseVectorOfIndexes(item, Reference::instance(), entry.reference));
      break;
    }
    case type::T50_MOD:
    {
      columnFlags.set(_column, parseIndex(item, Time50Mod::instance(), entry.t50.mod));
      break;
    }
    case type::T50:
    {
      columnFlags.set(_column, parseDouble(item, entry.t50.value));
      break;
    }
    case type::T50_ERROR:
    {
      columnFlags.set(_column, parseDouble(item, entry.t50.error));
      break;
    }
    case type::T50_RANGE:
    {
      columnFlags.set(_column, parseIntegerRange(item, entry.t50.range));
      break;
    }
    case type::T50_EMIN:
    {
      columnFlags.set(_column, parseInteger(item, entry.t50.emin));
      break;
    }
    case type::T50_EMAX:
    {
      columnFlags.set(_column, parseInteger(item, entry.t50.emax));
      break;
    }
    case type::T90_MOD:
    {
      columnFlags.set(_column, parseIndex(item, Time90Mod::instance(), entry.t90.mod));
      break;
    }
    case type::T90:
    {
      columnFlags.set(_column, parseDouble(item, entry.t90.value));
      break;
    }
    case type::T90_ERROR:
    {
      columnFlags.set(_column, parseDouble(item, entry.t90.error));
      break;
    }
    case type::T90_RANGE:
    {
      columnFlags.set(_column, parseIntegerRange(item, entry.t90.range));
      break;
    }
    case type::T90_EMIN:
    {
      columnFlags.set(_column, parseInteger(item, entry.t90.emin));
      break;
    }
    case type::T90_EMAX:
    {
      columnFlags.set(_column, parseInteger(item, entry.t90.emax));
      break;
    }
    case type::T_OTHER:
    {
      columnFlags.set(_column, parseDouble(item, entry.t_other.value));
      break;
    }
    case type::NOTES:
    {
      columnFlags.set(_column, parseString(item, entry.t_other.notes));
      break;
    }
    case type::FLUX_NOTES:
    {
      columnFlags.set(_column, parseString(item, entry.flux_notes));
      break;
    }
    case type::LOCAL_NOTES:
    {
      columnFlags.set(_column, parseString(item, entry.local_notes));
      break;
    }
    default:
    {
      std::stringstream ss;
      ss << "Parsing failed at row=" << _row+1 << ", column="<< _column+1
         << " [" << GlobalName::getColumn(_column) << "] is out of range.";
      Exception exc(ss.str(), PRETTY_FUNCTION);
      throw exc;
    }
  }
}

bool
Parser::parseVectorOfStrings(const std::string& raw, std::vector<std::string>& valueVector)
{
  std::stringstream ss(raw);
  for (std::string item; std::getline(ss, item, DELIM_LIST);)
  {
    valueVector.push_back(item);
  }
  return !valueVector.empty();
}

bool
Parser::parseVectorOfIndexes(const std::string& raw, NameMapper* mapper,
                             std::vector<type::Index>& valueVector)
{
  std::stringstream ss(raw);
  for (std::string item; std::getline(ss, item, DELIM_LIST);)
  {
    int index;
    parseIndex(item, mapper, index);
    valueVector.push_back(index);
  }
  return !valueVector.empty();
}

bool
Parser::parseTimePoint(const std::string& raw, type::Date& value)
{
  if (raw.empty())
  {
    return false;
  }
  value = std::chrono::system_clock::now();
  return true;
}

bool
Parser::parseString(const std::string& raw, std::string& value)
{
  value = std::move(raw);
  return !value.empty();
}

bool
Parser::parseIndex(const std::string& raw, NameMapper* mapper, type::Index& value)
{
  value = mapper->getIndex(raw);
  if (value == -1)
  {
    std::stringstream ss;
    ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
       << " [" << GlobalName::getColumn(_column) << "] for string=" << raw << " and mapper="
       << mapper->getColumnName();
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
Parser::parseIntegerRange(const std::string& raw, std::size_t (& value)[2])
{
  int i = 0;
  std::stringstream ss(raw);
  for (std::string item; std::getline(ss, item, DELIM_RANGE);)
  {
    parseInteger(item, value[i++]);
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
Parser::parseInteger(const std::string& raw, std::size_t& value)
{
  try
  { 
    int res = std::stoi(raw);
    if (res < 0)
    {
      return false;
    }
    value = (std::size_t) res;
  }
  catch (std::exception& sysExc)
  {
    std::stringstream ss;
    ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
       << " [" << GlobalName::getColumn(_column) << "] for int=" << raw
       << ". exc.what()=" << sysExc.what();
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
Parser::parseDouble(const std::string& raw, double& value)
{
  try
  {
    value = std::stod(raw);
  }
  catch (std::exception& sysExc)
  {
    std::stringstream ss;
    ss << "Parsing failed at row:column=" << _row+1 << ":" << _column+1
       << " [" << GlobalName::getColumn(_column) << "] for double=" << raw
       << ". exc.what()=" << sysExc.what();
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
Parser::parseFlag(const std::string& raw, bool& value)
{
  switch (raw[0])
  {
    case 'N':
    {
      value = false;
      break;
    }
    case 'Y':
    {
      value = true;
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

}
