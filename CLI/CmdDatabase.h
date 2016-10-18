#include "CLI/Cmd.h"
#include "Data/CatalogType.h"
#include "Data/DataBaseFormatType.h"

#pragma once

namespace grb
{

class DataBaseFormat;
class Catalog;
class Parser;

class CmdDatabase : public Cmd
{
public:
  CmdDatabase();
  ~CmdDatabase();

protected:
  bool doParse(std::list<std::string>& tokens);
  void doExecute();
  std::string doHelp(type::CommandHelpType type);

  virtual DataBaseFormat* getDbFormat(const type::DataBaseFormatType& dbType);
  virtual Catalog* getCatalog(type::DataBaseFormatType dbType);
  virtual Parser* getParser(DataBaseFormat& dbFormat, Catalog& catalog);

  bool filenameMapping(const std::string& filename);
  type::CatalogType convertDataBaseFormat(type::DataBaseFormatType dbType);

private:
  std::string _dbFilename;
  type::DataBaseFormatType _dbType;
  DataBaseFormat* _format = nullptr;
};

} // namespace grb
