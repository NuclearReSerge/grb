#include "Tools/ParserDatabase.h"

#include "Catalog/Catalog.h"
#include "Catalog/CatalogEntry.h"
#include "Catalog/CatalogEntryMapper.h"
#include "Data/ColumnMapper.h"
#include "Data/ValueMapper.h"
#include "Database/Database.h"
#include "Database/DatabaseColumn.h"
#include "Database/DatabaseMapper.h"
#include "Tools/NameMapper.h"

#include <sstream>
#include <fstream>

#include "Common/trace.h"

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

ParserDatabase::ParserDatabase(const std::string& filename, Database& database,
                               Catalog& catalog)
  : Parser(), _stream(nullptr), _database(database), _catalog(catalog),
    _columnsRequired(_database.getRequiredColumns()), _isSourceFile(false),  _columnIdx(0),
    _columnType(type::UNDEFINED_COLUMN), _valueType(type::UNDEFINED_VALUE)

{
  openFileStream(filename);
  checkFormat();
}

ParserDatabase::ParserDatabase(std::istream* stream, Database& database, Catalog& catalog)
  : Parser(), _stream(stream), _database(database), _catalog(catalog),
    _columnsRequired(_database.getRequiredColumns()), _isSourceFile(false),  _columnIdx(0),
    _columnType(type::UNDEFINED_COLUMN), _valueType(type::UNDEFINED_VALUE)
{
  if (!_stream)
  {
    Exception exc(type::EXCEPTION_CRITICAL,
                  "Parsing failed. Stream is nullptr.", PRETTY_FUNCTION);
    throw exc;
  }
  checkFormat();
}

ParserDatabase::~ParserDatabase()
{
  if (_isSourceFile)
  {
    static_cast<std::ifstream*>(_stream)->close();
    delete _stream;
  }
}

void
ParserDatabase::openFileStream(const std::string& filename)
{
  _stream = new std::ifstream(filename);

  if(_stream->fail())
  {
    delete _stream;

    std::stringstream ss;
    ss << "Parsing failed. Unable to open file '" << filename << "'.";
    Exception exc(type::EXCEPTION_CRITICAL, ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  _isSourceFile = true;
}

void
ParserDatabase::checkFormat()
{
  if (_database.getDataTypes().empty())
  {
    std::stringstream ss;
    ss << "Parsing failed. Database format '"
       << DatabaseMapper::instance()->getKey(_database.getType())
       << "' is undefined.";

    Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  for (const DatabaseColumn* dbCol : _database.getDataTypes())
  {
    if (dbCol->getColumnType() == type::UNDEFINED_COLUMN)
    {
      std::stringstream ss;
      ss << "Parsing failed. Database format '"
         << DatabaseMapper::instance()->getKey(_database.getType())
         << "' has undefined column type.";

      Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
      throw exc;
    }
  }
}

bool
ParserDatabase::parse()
{
//  for (std::size_t column = 0; column < type::UNDEFINED_COLUMN; ++column)
//    _catalog.setUnitType((type::ColumnType) _column, _database[_column].getUnitType());
  _rows = 0;

  for (std::string line; std::getline(*_stream, line);)
  {
    if (line.empty() || line[0] == COMMENT)
      continue;

    CatalogEntry* entry = _catalog.createEntry();
    if (!entry)
    {
      std::stringstream ss;
      ss << "Parsing failed. Catalog of type '"
         << CatalogEntryMapper::instance()->getKey(_catalog.getType())
         << "' creates invalid entries.";

      Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    try
    {
      parseLine(line, entry);
    }
    catch (Exception& exc)
    {
      delete entry;
      throw;
    }

    _catalog.getEntries().push_back(entry);
    ++_rows;
  }

  if (!_rows || _catalog.getEntries().empty())
  {
    Exception exc(type::EXCEPTION_WARNING, "Parsing failed. Stream or Catalog is empty.",
                  PRETTY_FUNCTION);
    throw exc;
  }

  return true;
}

void
ParserDatabase::parseLine(const std::string& line, CatalogEntry* entry)
{
  type::ColumnFlags columnFlags;
  std::stringstream ss(line);
  _columnIdx = 0;

  for (std::string element; std::getline(ss, element, DELIM_COLUMN);)
  {
    if (_columnIdx >= _database.getDataTypes().size())
    {
      std::stringstream ss;
      ss << "Parsing failed. Row=" << _rows + 1 << ". Line has more columns than expected.";
      Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    element.erase(0, element.find_first_not_of(WHITESPACE));
    element.erase(element.find_last_not_of(WHITESPACE) + 1);

    bool result = false;
    _columnType = type::UNDEFINED_COLUMN;
    try
    {
      _columnType = _database.getDataTypes()[_columnIdx]->getColumnType();
      result = parseMapper(element, entry);
    }
    catch (Exception& grbExc)
    {
      if (grbExc.getLevel() == type::EXCEPTION_CRITICAL)
      {
        std::stringstream ss;
        ss << std::endl << grbExc.what();
        Exception exc(type::EXCEPTION_CRITICAL,
                      getExceptionString(ss.str()),
                      PRETTY_FUNCTION);
        throw exc;
      }
      if(_columnsRequired.test(_columnType))
      {
        throw;
      }
    }
    columnFlags.set(_columnType, result);
    ++_columnIdx;
  }

  checkColumns(columnFlags);

  if (!entry->isValid())
  {
    std::stringstream ss;
    ss << "Parsing failed row=" << _rows + 1 << ". Data not valid.";
    Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
}

void
ParserDatabase::checkColumns(const type::ColumnFlags& columnFlags)
{
  const bool allRequired = ((columnFlags & _columnsRequired) ^ _columnsRequired).none();
  const bool allProcessed = _columnIdx == _database.getDataTypes().size();

  if (allProcessed && allRequired)
    return;

  std::stringstream ss;
  ss << "Parsing failed row=" << _rows + 1 << ". Columns of type={";

  if (!allProcessed)
  {
    std::size_t i = 0;
    for (const DatabaseColumn* dataType : _database.getDataTypes())
    {
      if (i++ < _columnIdx)
        continue;

      ss << i << " [" << ColumnMapper::instance()->getKey(dataType->getColumnType()) << "] ";
    }
    ss << "} not processed.";
  }
  else
  {
    std::size_t i = 0;
    for (const DatabaseColumn* dataType : _database.getDataTypes())
    {
      if (!columnFlags[dataType->getColumnType()])
        ss << i << " [" << ColumnMapper::instance()->getKey(dataType->getColumnType()) << "] ";
      ++i;
    }
    ss << "} require valid values.";
  }
  Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
  throw exc;
}

bool
ParserDatabase::parseMapper(const std::string& raw, CatalogEntry* entry)
{
  bool result = false;
  _valueType = _database.getDataTypes()[_columnIdx]->getValueType();

  switch (_valueType)
  {
    case type::FLAG:
      result = parseValue(raw, entry->getFlag(_columnType));
      break;
    case type::INTEGER:
      result = parseValue(raw, entry->getInteger(_columnType));
      break;
    case type::INDEX:
      result = parseValue(raw, entry->getMapper(_columnType), entry->getIndex(_columnType));
      break;
    case type::INTEGER_RANGE:
      result = parseValue(raw, entry->getIntegerRange(_columnType));
      break;
    case type::INDEX_LIST:
      result = parseValue(raw, entry->getMapper(_columnType), entry->getIndexList(_columnType));
      break;
    case type::FLOAT:
      result = parseValue(raw, entry->getFloat(_columnType));
      break;
    case type::STRING:
      result = parseValue(raw, entry->getString(_columnType));
      break;
    case type::STRING_LIST:
      result = parseValue(raw, entry->getStringList(_columnType));
      break;
    default:
    {
      Exception exc(type::EXCEPTION_WARNING,
                    getExceptionString("Value type is not supported."),
                    PRETTY_FUNCTION);
      throw exc;
    }
  }
  return result;
}

bool
ParserDatabase::parseValue(const std::string& raw, type::Flag* value)
{ 
  if (!value)
  {
    Exception exc(type::EXCEPTION_WARNING,
                  getExceptionString("Column-Value mapping failed."),
                  PRETTY_FUNCTION);
    throw exc;
  }

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
  ss << "Raw string=" << raw << ".";
  Exception exc(type::EXCEPTION_WARNING, getExceptionString(ss.str()), PRETTY_FUNCTION);
  throw exc;
}

bool
ParserDatabase::parseValue(const std::string& raw, type::Integer* value)
{
  if (raw.empty())
    return false;

  if (!value)
  {
    Exception exc(type::EXCEPTION_WARNING,
                  getExceptionString("Column-Value mapping failed."),
                  PRETTY_FUNCTION);
    throw exc;
  }

  try
  {
    long res = std::stol(raw);
    if (res < 0)
    {
      return false;
    }
    *value = (std::size_t) res;
  }
  catch (std::exception& stdExc)
  {
    std::stringstream ss;
    ss << "Raw string=" << raw << ".";
    ss << std::endl << "std::exception.what()=" << stdExc.what() << ".";
    Exception exc(type::EXCEPTION_WARNING, getExceptionString(ss.str()), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
ParserDatabase::parseValue(const std::string& raw, const mapper::NameMapper* mapper, type::Index* value)
{
  if (raw.empty())
    return false;

  if (!mapper || !value)
  {
    Exception exc(type::EXCEPTION_WARNING,
                  getExceptionString(!value ? "Column-Value mapping failed." :
                                              "NameMapper not found."),
                  PRETTY_FUNCTION);
    throw exc;
  }

  try
  {
    *value = mapper->getIndex(raw);
  }
  catch (Exception& mapExc)
  {
    std::stringstream ss;
    ss << "Raw string=" << raw << ".";
    ss << std::endl << mapExc.what();
    Exception exc(type::EXCEPTION_WARNING, getExceptionString(ss.str()), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
ParserDatabase::parseValue(const std::string& raw, type::IntegerRange* value)
{
  if (raw.empty())
    return false;

  if (!value)
  {
    Exception exc(type::EXCEPTION_WARNING,
                  getExceptionString("Column-Value mapping failed."),
                  PRETTY_FUNCTION);
    throw exc;
  }

  int i = 0;
  std::stringstream ssRaw(raw);
  for (std::string item; std::getline(ssRaw, item, DELIM_RANGE);)
  {
    ++i;
    type::Integer val;
    if (parseValue(item, &val))
    {
      value->push_back(val);
    }
  }

  if (value->size() == 2 && i == 2)
    return true;

  std::stringstream ss;
  ss << "Raw string=" << raw << ".";
  Exception exc(type::EXCEPTION_WARNING, getExceptionString(ss.str()), PRETTY_FUNCTION);
  throw exc;
}

bool
ParserDatabase::parseValue(const std::string& raw, const mapper::NameMapper* mapper,
                           type::IndexList* valueList)
{
  if (raw.empty())
    return false;

  if (!valueList)
  {
    Exception exc(type::EXCEPTION_WARNING,
                  getExceptionString(!valueList ? "Column-Value mapping failed." :
                                                  "NameMapper not found."),
                  PRETTY_FUNCTION);
    throw exc;
  }

  std::size_t i = 0;
  std::stringstream ssRaw(raw);
  for (std::string item; std::getline(ssRaw, item, DELIM_LIST);)
  {
    ++i;
    item.erase(0, item.find_first_not_of(WHITESPACE));
    item.erase(item.find_last_not_of(WHITESPACE) + 1);

    if(item.empty())
      continue;

    int index;
    parseValue(item, mapper, &index);
    valueList->push_back(index);
  }

  if (!valueList->empty() && valueList->size() == i)
    return true;

  std::stringstream ss;
  ss << "Raw string=" << raw << ".";
  Exception exc(type::EXCEPTION_WARNING, getExceptionString(ss.str()), PRETTY_FUNCTION);
  throw exc;
}

bool
ParserDatabase::parseValue(const std::string& raw, type::Float* value)
{
  if (raw.empty())
    return false;

  if (!value)
  {
    Exception exc(type::EXCEPTION_WARNING,
                  getExceptionString("Column-Value mapping failed."),
                  PRETTY_FUNCTION);
    throw exc;
  }

  try
  {
    *value = std::stod(raw);
  }
  catch (std::exception& stdExc)
  {
    std::stringstream ss;
    ss << "Raw string=" << raw << ".";
    ss << std::endl << "std::exception.what()=" << stdExc.what() << ".";
    Exception exc(type::EXCEPTION_WARNING, getExceptionString(ss.str()), PRETTY_FUNCTION);
    throw exc;
  }
  return true;
}

bool
ParserDatabase::parseValue(const std::string& raw, type::String* value)
{
  if (raw.empty())
    return false;

  if (!value)
  {
    Exception exc(type::EXCEPTION_WARNING,
                  getExceptionString("Column-Value mapping failed."),
                  PRETTY_FUNCTION);
    throw exc;
  }

  *value = raw;
  return !value->empty();
}

bool
ParserDatabase::parseValue(const std::string& raw, type::StringList* valueList)
{
  if (raw.empty())
    return false;

  if (!valueList)
  {
    Exception exc(type::EXCEPTION_WARNING,
                  getExceptionString("Column-Value mapping failed."),
                  PRETTY_FUNCTION);
    throw exc;
  }

  std::stringstream ss(raw);
  for (std::string item; std::getline(ss, item, DELIM_LIST);)
  {
    item.erase(0, item.find_first_not_of(WHITESPACE));
    item.erase(item.find_last_not_of(WHITESPACE) + 1);
    if (item.empty())
      return false;

    valueList->push_back(item);
  }

  return !valueList->empty();
}

std::string
ParserDatabase::getExceptionString(std::string cause)
{
  std::stringstream ss;
  ss << "Parsing failed row=" << _rows + 1 << ", column=" << _columnIdx+1
     << ", column type=" << _columnType << " [" << ColumnMapper::instance()->getKey(_columnType)
     << "], value type=" << _valueType << " [" << ValueMapper::instance()->getKey(_valueType)
     << "]. " << cause;
  return ss.str();
}

}
