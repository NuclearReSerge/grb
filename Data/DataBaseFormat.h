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
  virtual ~DataBaseFormat();

  type::DatabaseTableType getType() const;
  type::CoordinateSystemType getCoordinateSystem() const;
  std::size_t getSize() const;
  const type::ColumnFlags& getRequiredColumns() const;
  const DataType& getColumnFormat(const std::size_t column) const throw(Exception);

protected:
  void initialize();
  virtual void doInit();
  void initHEASARC_GRBCAT();

  const type::DatabaseTableType _type;
  type::CoordinateSystemType _coordSys;
  type::ColumnFlags _requiredFlags;
  std::vector<DataType*> _format;
};

class DataBaseFormatFactory
{
public:
  const DataBaseFormat* getFormat(const type::DatabaseTableType dbType) throw(Exception);

protected:
  friend class Singleton<DataBaseFormatFactory>;
  DataBaseFormatFactory();

private:
  DataBaseFormat _HEASARC_GRBCAT;
};

typedef Singleton<DataBaseFormatFactory> DataBaseFormats;

}
