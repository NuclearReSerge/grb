#include "CLI/CmdDatabase.h"

#include "CLI/CommandMapper.h"
#include "Data/Catalog.h"
#include "Data/CatalogEntryType.h"
#include "Data/DataBaseFormatFactory.h"
#include "Main/AnalysisData.h"
#include "Tools/Parser.h"

#include <iostream>
#include <sstream>

namespace
{

const char* TDAT_FILE_EXT = "tdat";
const char* HELP_SHORT = "reads the database file and creates a catalog.";
const char* HELP_LONG = "[<DB_FILE>]\n"
"\n"
"    DB_FILE : name of the database file.\n"
"\n"
"Available databases:\n";

} // namespace

namespace grb
{

type::CatalogEntryType
convertDataBaseFormat(type::DatabaseFormatType dbType)
{
  switch (dbType)
  {
    case type::HEASARC_GRBCAT:
      return type::GRBCAT_ENTRY;

    case type::HEASARC_GRBCATAG:
    case type::HEASARC_GRBCATANN:
    case type::HEASARC_GRBCATBOX:
    case type::HEASARC_GRBCATCIRC:
    case type::HEASARC_GRBCATDUAL:
    case type::HEASARC_GRBCATFLUX:
    case type::HEASARC_GRBCATINT:
    case type::HEASARC_GRBCATINTA:
    case type::HEASARC_GRBCATIRR:
    default:
      break;
  }
  return type::UNDEFINED_CATALOG_ENTRY;
}

CmdDatabase::CmdDatabase()
  : Cmd(type::CMD_DATABASE)
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
    ss << "Error while parsing command " << CommandMapper::instance()->getKey(getType())
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
  DataBaseFormat* dbFormat = DataBaseFormatFactory::instance()->createName(_dbFile);

  if (!dbFormat)
  {
    std::stringstream ss;
    ss << "Error while executing command " << CommandMapper::instance()->getKey(getType())
       << ". Database format for file " << _dbFile << " unavailable.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  type::DatabaseFormatType dbType = dbFormat->getType();
  std::printf("Database table: %s\n",
              DataBaseFormatMapper::instance()->getKey(dbType).c_str());

  type::CatalogEntryType catType = convertDataBaseFormat(dbType);

  if (catType == type::UNDEFINED_CATALOG_ENTRY)
  {
    std::stringstream ss;
    ss << "Error while executing command " << CommandMapper::instance()->getKey(getType())
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
    ss << "Error while executing command " << CommandMapper::instance()->getKey(getType())
       << ". Parser exception." << std::endl << parseExc.what();
    Exception exc(parseExc.getLevel(), ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  std::cout << "Parsing of database successful. Extraced " << rows << " rows." << std::endl;

  G_CatalogData().reset(catalog);
}

std::string
CmdDatabase::doHelp(type::CommandHelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  std::stringstream ss;
  ss << HELP_LONG;
  for(int i = 0; i < type::UNDEFINED_DATABASE_FORMAT; ++i)
  {
    ss << "  "
       << DataBaseFormatMapper::instance()->getKey((type::DatabaseFormatType) i)
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

} // namespace grb
