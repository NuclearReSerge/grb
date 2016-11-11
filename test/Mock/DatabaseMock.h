#pragma once

#include "Database/Database.h"

#include <gmock/gmock.h>

namespace grb
{

class DatabaseMock : public Database
{
public:
  DatabaseMock(const type::DatabaseType dbType)
    : Database(dbType)
  {
  }

  void addColumn(DatabaseColumn* dataType) { Database::addColumn(dataType); }
  void setColumnFlag(std::size_t column, bool required = true)
  {
    Database::setColumnFlag(column, required);
  }
  void setColumnFlags() { Database::setColumnFlags(); }

  MOCK_METHOD2(doParse, bool(type::DatabaseCmdType cmd, std::list<std::string>& tokens));
  MOCK_METHOD1(doExecute, void(type::DatabaseCmdType cmd));
  MOCK_METHOD0(doHelp, std::string());
  MOCK_METHOD0(initialize, void());
};

} // namespace grb
