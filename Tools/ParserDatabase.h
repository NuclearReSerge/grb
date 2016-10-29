#include "Common/Exception.h"
#include "Common/Global.h"
#include "Data/ColumnType.h"
#include "Data/DataBaseColumn.h"
#include "Tools/Parser.h"

#include <iostream>
#include <string>

#pragma once

namespace grb
{

class Catalog;
class CatalogEntry;
class DataBaseFormat;

namespace mapper
{
class NameMapper;
}


class ParserDatabase : public Parser
{
public:
  ParserDatabase() = delete;
  ParserDatabase(const std::string& filename, DataBaseFormat& format, Catalog& catalog);
  ParserDatabase(std::istream* stream, DataBaseFormat& format, Catalog& catalog);
  ~ParserDatabase();

  virtual bool parse() override;

protected:
  void openFileStream(const std::string& filename);
  void checkFormat();

  void parseLine(const std::string& line, CatalogEntry* entry);
  void checkColumns(const type::ColumnFlags& columnFlags);

  bool parseMapper(const std::string& raw, CatalogEntry* entry);

  bool parseValue(const std::string& raw, type::Flag* value);
  bool parseValue(const std::string& raw, type::Integer* value);
  bool parseValue(const std::string& raw, const mapper::NameMapper* mapper, type::Index* value);
  bool parseValue(const std::string& raw, type::IntegerRange* value);
  bool parseValue(const std::string& raw, const mapper::NameMapper* mapper, type::IndexList* valueList);
  bool parseValue(const std::string& raw, type::Float* value);
  bool parseValue(const std::string& raw, type::String* value);
  bool parseValue(const std::string& raw, type::StringList* valueList);

  std::string getExceptionString(std::string cause);

private:
  std::istream* _stream;
  DataBaseFormat& _format;
  Catalog& _catalog;
  const type::ColumnFlags& _columnsRequired;


  bool _isSourceFile;
  std::size_t _columnIdx;
  type::ColumnType _columnType;
  type::ValueType _valueType;

};

} // namespace grb
