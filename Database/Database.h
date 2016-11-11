#pragma once

#include "Common/BaseObject.h"
#include "Database/DatabaseCmdType.h"
#include "Database/DatabaseColumn.h"
#include "Database/DatabaseType.h"

#include <vector>

namespace grb
{

typedef BaseObject<type::DatabaseType, type::DatabaseCmdType> DatabaseBase;

class Database : public DatabaseBase
{
public:
  Database(type::DatabaseType type = type::UNDEFINED_DATABASE)
    : DatabaseBase(type)
  {
  }

  virtual ~Database()
  {
    for (DatabaseColumn* item : _format)
    {
      delete item;
    }
    _format.clear();
  }

  const type::ColumnFlags& getRequiredColumns() const
  {
    return _requiredFlags;
  }

  const std::vector<DatabaseColumn*>& getDataTypes() const
  {
    return _format;
  }

  std::vector<DatabaseColumn*>& getDataTypes()
  {
    return _format;
  }

  virtual void initialize() = 0;

protected:

protected:
  bool isCommandValid(const type::DatabaseCmdType cmd)
  {
    switch (cmd)
    {
      case type::DATABASE_CREATE:
      case type::DATABASE_HELP:
      {
        return false;
      }
      default:
        return true;
    }
  }

  void addColumn(DatabaseColumn* dbColumn)
  {
    _format.push_back(dbColumn);
  }

  void setColumnFlag(std::size_t column, bool required = true)
  {
    _requiredFlags.set(column, required);
  }

  void setColumnFlags()
  {
    for (const DatabaseColumn* item : _format)
    {
      _requiredFlags.set(item->getColumnType(), item->isColumnRequired());
    }
  }

private:
  type::ColumnFlags _requiredFlags;
  std::vector<DatabaseColumn*> _format;
};

}
