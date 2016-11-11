#pragma once

#include "CLI/Cmd.h"

#include "Database/DatabaseCmdType.h"
#include "Database/DatabaseType.h"

namespace grb
{

typedef Cmd<type::DatabaseType, type::DatabaseCmdType> CmdDatabaseBase;

class CmdDatabase : public CmdDatabaseBase
{
public:
  CmdDatabase()
    : CmdDatabaseBase(type::CMD_DATABASE)
  {
  }

protected:
  type::DatabaseType getMappedObjectVal(std::string& objStr) override;
  type::DatabaseCmdType getMappedSubCmdVal(std::string& cmdStr) override;
  std::string getMappedSubCmdStr(type::DatabaseCmdType cmdVal) override;
  bool isObjectCreated() override;
  std::string getCreatedObjectName() override;
  bool doParse(std::list<std::string>& tokens) override;
  void doExecute() override;
  std::string doHelp(type::CommandHelpType type) override;
  void executeCreate() override;
  void executeHelp() override;

private:
  type::DatabaseCmdType _subCmd;
  type::DatabaseType _type;
};

} // namespace grb

/*
#include "Catalog/CatalogType.h"

class Catalog;
class Database;
class Parser;
~CmdDatabase();
  virtual Database* getDatabase(const type::DatabaseType& dbType);
  virtual Catalog* getCatalog(type::DatabaseType dbType);
  virtual Parser* getParser(Database& database, Catalog& catalog);

  bool filenameMapping(const std::string& filename);
  type::CatalogType convertDatabase(type::DatabaseType dbType);
  std::string _dbFilename;
  Database* _format = nullptr;

*/

