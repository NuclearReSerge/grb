#include "Common/Exception.h"
#include "Common/Global.h"

#include <istream>
#include <string>

#pragma once

namespace grb
{

class Catalog;
class CatalogEntry;
class DataBaseFormat;
class Exception;
class NameMapper;

class Parser
{
public:
  Parser(const std::string& filename, const DataBaseFormat& format, Catalog& catalog);
  Parser(std::istream* stream, const DataBaseFormat& format, Catalog& catalog);
  ~Parser();

  std::size_t parse() throw(Exception);

protected:
  void openFileStream(const std::string& filename);

  void parseLine(const std::string& line, CatalogEntry* entry);
  void checkColumns(const type::ColumnFlags& columnFlags);

  bool parseMapper(const std::string& raw, CatalogEntry* entry);

  bool parseValue(const std::string& raw, type::Flag* value);
  bool parseValue(const std::string& raw, type::Integer* value);
  bool parseValue(const std::string& raw, const NameMapper* mapper, type::Index* value);
  bool parseValue(const std::string& raw, type::IntegerRange* value);
  bool parseValue(const std::string& raw, const NameMapper* mapper, type::IndexList* valueList);
  bool parseValue(const std::string& raw, type::Float* value);
  bool parseValue(const std::string& raw, type::String* value);
  bool parseValue(const std::string& raw, type::StringList* valueList);

  std::string getExceptionString(std::string cause);

private:
  bool _isSourceFile;
  std::istream* _stream;
  std::size_t _row;
  std::size_t _column;
  type::ColumnType _columnType;
  type::ValueType _valueType;

  const DataBaseFormat& _format;
  const type::ColumnFlags& _columnsRequired;
  Catalog& _catalog;
};

}
