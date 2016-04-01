#include "Common/Exception.h"
#include "Data/Catalog.h"
#include "Data/DataBaseFormat.h"
#include "Tools/NameMapper.h"

#include <istream>
#include <string>

#pragma once

namespace grb
{

class Parser
{
public:
  Parser() = delete;
  Parser(const std::string& filename);
  Parser(std::istream* stream);
  ~Parser();

  std::size_t parse(const DataBaseFormat& format, Catalog& catalog) throw(Exception);

protected:
  void openFileStream(const std::string& filename) throw(Exception);

  void parseMapper(CatalogEntry& entry, type::ColumnFlags& columnFlags, const std::string& item) throw(Exception);
  bool parseVectorOfStrings(const std::string& raw, std::vector<std::string>& valueVector);
  bool parseVectorOfIndexes(const std::string& raw, NameMapper* mapper,
                            std::vector<type::Index>& valueVector);
  bool parseTimePoint(const std::string& raw, type::Date& value);
  bool parseString(const std::string& raw, std::string& value);
  bool parseIndex(const std::string& raw, NameMapper* mapper, type::Index& value);
  bool parseIntegerRange(const std::string& raw, std::size_t (& value)[2]);
  bool parseInteger(const std::string& raw, std::size_t& value);
  bool parseDouble(const std::string& raw, double& value);
  bool parseFlag(const std::string& raw, bool& value);

  // time_point
private:
  bool _isSourceFile {false};
  std::istream* _stream;
  std::size_t _row;
  type::ColumnType _column;
};

}
