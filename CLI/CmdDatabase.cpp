#include "CLI/CmdDatabase.h"

#include "Data/Catalog.h"
#include "Data/DataBaseFormatFactory.h"
#include "Main/AnalysisData.h"
#include "Tools/Parser.h"

#include <iostream>
#include <sstream>

namespace grb
{

namespace
{

const char* TDAT_FILE_EXT = "tdat";
const char* HELP_SHORT = "reads the database file and creates a catalog.";
const char* HELP_LONG = "[<DB_FILE>]\n"
"\n"
"    DB_FILE : name of the database file.\n"
"\n"
"Available databases:\n";
}

CmdDatabase::CmdDatabase(CommandLine& cli)
  : Cmd(cli, type::CMD_DATABASE)
{
}

bool
CmdDatabase::doParse(std::list<std::string>& tokens)
{
  if (tokens.empty())
  {
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  help(type::HELP_LONG), PRETTY_FUNCTION);
    throw exc;
  }

  if (!filenameMapping(tokens.front()))
  {
    std::stringstream ss;
    ss << "Error while parsing command " << CmdMapper::instance()->getKey(getType())
       << ". Filename " << tokens.front() << " not recognized.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  tokens.pop_front();

  return true;
}

void
CmdDatabase::doExecute()
{
  DataBaseFormat* dbFormat = DataBaseFormatFactory::instance()->create(_dbFile);

  if (!dbFormat)
  {
    std::stringstream ss;
    ss << "Error while executing command " << CmdMapper::instance()->getKey(getType())
       << ". Database format for file " << _dbFile << " unavailable.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  type::DatabaseTableType dbType = dbFormat->getType();
  std::printf("Database table: %s\n",
              DataBaseFormatMapper::instance()->getKey(dbType).c_str());

  type::CatalogEntryType catType = CatalogEntryMapper::instance()->convertDataBaseFormat(dbType);

  if (catType == type::UNDEFINED_CATALOG_ENTRY)
  {
    std::stringstream ss;
    ss << "Error while executing command " << CmdMapper::instance()->getKey(getType())
       << ". Catalog for database format " << DataBaseFormatMapper::instance()->getKey(dbType)
       << " unavailable.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  Catalog* catalog = new Catalog(catType);

  std::size_t rows;
  try
  {
    Parser parser(_dbFilename, *dbFormat, *catalog);
    rows = parser.parse();
  }
  catch (grb::Exception& parseExc)
  {
    std::stringstream ss;
    ss << "Error while executing command " << CmdMapper::instance()->getKey(getType())
       << ". Parser exception." << std::endl << parseExc.what();
    Exception exc(parseExc.getLevel(), ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  std::cout << "Parsing of database successful. Extraced " << rows << " rows." << std::endl;

  G_CatalogData().reset(catalog);
}

std::string
CmdDatabase::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  std::stringstream ss;
  ss << HELP_LONG;
  for(int i = 0; i < type::UNDEFINED_DATABASE_TABLE; ++i)
  {
    ss << "  "
       << DataBaseFormatMapper::instance()->getKey((type::DatabaseTableType) i)
       << "."<< TDAT_FILE_EXT << std::endl;
  }

  return ss.str();
}

bool
CmdDatabase::filenameMapping(const std::string& filename)
{
  std::size_t pos = filename.find_first_of(".");
  if (pos == std::string::npos)
    return false;

  std::string fileext = filename.substr(pos+1);
  if (fileext.compare(TDAT_FILE_EXT) != 0)
    return false;

  _dbFile = filename.substr(0, pos);
  _dbFilename = filename;

  std::printf("File:           %s\n",
              _dbFilename.c_str());


  return true;
}

}
