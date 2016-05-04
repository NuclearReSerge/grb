#include "CLI/Cmd.h"
#include "Common/Global.h"

#pragma once

namespace grb
{

class CmdDatabase : public Cmd
{
public:
  CmdDatabase(CommandLine& cli);

  bool parse(std::list<std::string>& args) throw(Exception);

  std::string getDbFilename() const;
  type::DatabaseTableType getDbType() const;
  type::CatalogType getCatType() const;

protected:
  std::string doHelp(type::HelpType type);
  void doExecute(Analyzer& analyzer);

  bool filenameMapping(const std::string& filename);

private:
  std::string _dbFile;
  type::DatabaseTableType _dbType;
  type::CatalogType _catType;


};

}
