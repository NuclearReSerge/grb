#include "CLI/CommandMapper.h"
#include "Common/GlobalName.h"
#include "Data/Catalog.h"
#include "Data/DataBaseFormatFactory.h"
#include "Main/AnalysisData.h"
#include "Tools/Parser.h"

#include "CLI/CmdDatabase.h"

#include <iostream>
#include <sstream>

namespace grb
{

namespace
{

const char* TDAT_FILE_EXT = "tdat";
const char* HELP_SHORT = " - reads the database file and creates a catalog.";
const char* HELP_LONG = " <DB_FILE>.tdat";

}

CmdDatabase::CmdDatabase(CommandLine& cli)
  : Cmd(cli, type::CMD_DATABASE)
{
}

bool
CmdDatabase::doParse(std::list<std::string>& args)
{
  if (args.empty())
  {
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  help(type::HELP_LONG), PRETTY_FUNCTION);
    throw exc;
  }

  if (!filenameMapping(args.front()))
  {
    std::stringstream ss;
    ss << "Command " << CommandMapper::instance()->getKey(getType())
       << " failed to open file " << args.front();
    Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                  ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  args.pop_front();

  return true;
}

void
CmdDatabase::doExecute()
{
  std::size_t rows;

  G_CatalogData().reset(new Catalog(_catType));

  try
  {
    Parser parser(_dbFile,
                  DataBaseFormatFactory::instance()->getFormat(_dbType),
                  *G_CatalogData().get());
    rows = parser.parse();
  }
  catch (grb::Exception& parseExc)
  {
    std::stringstream ss;
    ss << "Parsing failed." << std::endl << parseExc.what();
    Exception exc(parseExc.getLevel(), ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
  std::cout << "Parsing successful. Extraced " << rows << " rows." << std::endl;
}

std::string
CmdDatabase::doHelp(type::HelpType type)
{
  if (type == type::HELP_SHORT)
    return HELP_SHORT;

  return HELP_LONG;
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

  std::string basename = filename.substr(0, pos);

  for (int i = 0; i <type::DATABASE_TABLE_TYPE_UNDEFINED; ++i)
  {
    if (basename.compare(GlobalName::getDatabaseTable((type::DatabaseTableType) i)) == 0)
    {
      _dbType = (type::DatabaseTableType) i;
      break;
    }
  }

  switch (_dbType)
  {
    case type::HEASARC_GRBCAT:
    {
      _catType = type::GRBCAT;
      break;
    }

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
      return false;
  }
  _dbFile = filename;

  std::printf("File:           %s\nDatabase table: %s\nCatalog:        %s\n",
              _dbFile.c_str(),
              GlobalName::getDatabaseTable(_dbType).c_str(),
              GlobalName::getCatalog(_catType).c_str());
  return true;
}

}
