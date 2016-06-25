#include "CLI/Cmd.h"
#include "Common/Global.h"

#pragma once

namespace grb
{

class CmdDatabase : public Cmd
{
public:
  CmdDatabase(CommandLine& cli);

protected:
  bool doParse(std::list<std::string>& args);
  void doExecute();
  std::string doHelp(type::HelpType type);

  bool filenameMapping(const std::string& filename);

private:
  std::string _dbFile;
  type::DatabaseTableType _dbType;
  type::CatalogType _catType;


};

}
