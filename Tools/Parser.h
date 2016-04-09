#include "Common/Exception.h"
#include "Data/Catalog.h"
#include "Data/DataBaseFormat.h"
#include "Tools/NameMapper.h"

#include <istream>
#include <string>
#include <map>

#pragma once

namespace grb
{

class Parser
{
public:
  Parser(const std::string& filename, const DataBaseFormat* format, Catalog* catalog);
  Parser(std::istream* stream, const DataBaseFormat* format, Catalog* catalog);
  ~Parser();

  std::size_t parse() throw(Exception);

protected:
  Parser();
  void openFileStream(const std::string& filename);

  bool parseMapper(const std::string& raw, CatalogEntry* entry);
  bool parseValue(const std::string& raw, type::Flag* value);
  bool parseValue(const std::string& raw, type::Integer* value);
  bool parseValue(const std::string& raw, const NameMapper* mapper, type::Index* value);
  bool parseValue(const std::string& raw, type::IntegerRange* value);
  bool parseValue(const std::string& raw, const NameMapper* mapper, type::IndexList* valueList);
  bool parseValue(const std::string& raw, type::Float* value);
  bool parseValue(const std::string& raw, type::TimePoint* value);
  bool parseValue(const std::string& raw, type::String* value);
  bool parseValue(const std::string& raw, type::StringList* valueList);

  void throwException(type::ValueType valueType);
private:
  bool _isSourceFile;
  std::istream* _stream;
  std::size_t _row;
  std::size_t _column;
  type::ColumnType _columnType;

  const DataBaseFormat* _format;
  Catalog* _catalog;
};

}
