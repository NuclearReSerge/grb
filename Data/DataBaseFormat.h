#include "Data/DataType.h"
#include "Common/Exception.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class DataBaseFormat
{
public:
  DataBaseFormat() = delete;
  DataBaseFormat(const type::DatabaseTableType dbType);
  ~DataBaseFormat();

  type::DatabaseTableType getType() const;
  const DataType& getColumnFormat(const std::size_t column) const throw(Exception);
  std::size_t getSize() const;
  const type::ColumnFlags& getRequiredColumns() const;

protected:
  void initHEASARC_GRBCAT();

private:
  const type::DatabaseTableType _type;
  std::vector<DataType*> _format;
  type::ColumnFlags _requiredFlags;
};

class DataBaseFormatFactory
{
public:
  const DataBaseFormat& getFormat(const type::DatabaseTableType dbType) throw(Exception);

protected:
  friend class Singleton<DataBaseFormatFactory>;
  DataBaseFormatFactory();

private:
  DataBaseFormat _HEASARC_GRBCAT;
};

typedef Singleton<DataBaseFormatFactory> DataBaseFormats;

}
