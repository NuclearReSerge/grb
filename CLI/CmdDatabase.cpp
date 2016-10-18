#include "CLI/CmdDatabase.h"

#include "CLI/CommandMapper.h"
#include "Data/Catalog.h"
#include "Data/CatalogType.h"
#include "Data/DataBaseFormatFactory.h"
#include "Main/AnalysisData.h"
#include "Tools/ParserDatabase.h"

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

CmdDatabase::CmdDatabase()
  : Cmd(type::CMD_DATABASE)
{
}

CmdDatabase::~CmdDatabase()
{
  delete _format;
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

  _format = getDbFormat(_dbType);

  if (!_format)
  {
    std::stringstream ss;
    ss << "Error while executing command " << CommandMapper::instance()->getKey(getType())
       << ". Database format for file " << _dbFilename << " unavailable.";
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  std::cout << "Database table: "
            << DataBaseFormatMapper::instance()->getKey(_dbType).c_str() << std::endl;

  return true;
}

void
CmdDatabase::doExecute()
{
  Catalog* catalog = getCatalog(_dbType);

  if (!catalog)
  {
    std::stringstream ss;
    ss << "Error while executing command " << CommandMapper::instance()->getKey(getType())
       << ". Catalog not created.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  Parser* parser = getParser(*_format, *catalog);

  if (!parser)
  {
    delete catalog;

    std::stringstream ss;
    ss << "Error while executing command " << CommandMapper::instance()->getKey(getType())
       << ". Parser not created.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  bool result = false;
  std::size_t rows = 0;

  try
  {
    result = parser->parse();
    rows = parser->getNumberOfRows();
    delete parser;
  }
  catch (grb::Exception& parseExc)
  {
    delete catalog;
    delete parser;

    std::stringstream ss;
    ss << "Error while executing command " << CommandMapper::instance()->getKey(getType())
       << ". Parser exception." << std::endl
       << parseExc.what();
    Exception exc(parseExc.getLevel() | type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  if (!result)
  {
    std::cout << "Parsing of database failed. Extraced "
              << rows << " rows." << std::endl;
    return;
  }

  std::cout << "Parsing of database successful. Extraced "
            << rows << " rows." << std::endl;

  AnalysisData::instance()->setCatalogData(catalog);
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
       << DataBaseFormatMapper::instance()->getKey((type::DataBaseFormatType) i)
       << "."<< TDAT_FILE_EXT << std::endl;
  }

  return ss.str();
}

DataBaseFormat*
CmdDatabase::getDbFormat(const type::DataBaseFormatType& dbType)
{
  return DataBaseFormatFactory::instance()->createType(dbType);
}

Catalog*
CmdDatabase::getCatalog(type::DataBaseFormatType dbType)
{
  type::CatalogType catType = convertDataBaseFormat(dbType);

  if (catType == type::UNDEFINED_CATALOG)
  {
    std::stringstream ss;
    ss << "Error while executing command " << CommandMapper::instance()->getKey(getType())
       << ". Catalog for database format " << DataBaseFormatMapper::instance()->getKey(_dbType)
       << " unavailable.";
    Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  return new Catalog(catType);
}

Parser*
CmdDatabase::getParser(DataBaseFormat& dbFormat, Catalog& catalog)
{
  return new ParserDatabase(_dbFilename, dbFormat, catalog);
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

  try
  {
    _dbType =  DataBaseFormatMapper::instance()->getValue(filename.substr(0, pos));
  }
  catch (Exception& )
  {
    return false;
  }

  _dbFilename = filename;
  std::cout << "File:           " << _dbFilename.c_str() << std::endl;

  return true;
}

type::CatalogType
CmdDatabase::convertDataBaseFormat(type::DataBaseFormatType dbType)
{
  switch (dbType)
  {
    case type::HEASARC_GRBCAT:
      return type::GRBCAT;

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
  return type::UNDEFINED_CATALOG;
}

} // namespace grb
