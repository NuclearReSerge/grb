#include "Common/GlobalName.h"
#include <cstdio>

namespace grb
{

namespace
{
  const char* LINE_78_ASTER = "******************************************************************************";
  const char* PROGRAM_NAME = "Gamma-Ray Burst Correlation Analyzer";
  const char* TDAT_FILE_EXT = "tdat";
}

void
intro()
{
  std::printf("*%s*\n*%78s*\n* %s ver. %2.2f%s%30s*\n*%78s*\n*%s*\n\n",
              LINE_78_ASTER,
              "",
              PROGRAM_NAME, GRB_VERSION, (GRB_VERSION < 10.0 ? " " : ""), "",
              "",
              LINE_78_ASTER);
}

void
usage(const char* binName)
{
  std::printf("Usage: %s <DB_FILE_NAME>.tdat\n\n\t<DB_FILE_NAME> : name corresponding to database "
              "table name form dbms1.gsfc.nasa.gov\n\n",
              binName);
}

bool filenameMapping(const std::string& filename, type::DatabaseTableType& dbType,
                     type::CatalogType& catType)
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
      dbType = (type::DatabaseTableType) i;
      break;
    }
  }

  switch (dbType)
  {
    case type::HEASARC_GRBCAT:
    {
      catType = type::GRBCAT;
      break;
    }
/*
    case type::HEASARC_GRBCATAG:
    case type::HEASARC_GRBCATANN:
    case type::HEASARC_GRBCATBOX:
    case type::HEASARC_GRBCATCIRC:
    case type::HEASARC_GRBCATDUAL:
    case type::HEASARC_GRBCATFLUX:
    case type::HEASARC_GRBCATINT:
    case type::HEASARC_GRBCATINTA:
    case type::HEASARC_GRBCATIRR:
*/
    default:
      return false;
  }

  std::printf("File:           %s\nDatabase table: %s\nCatalog:        %s\n",
              filename.c_str(),
              GlobalName::getDatabaseTable(dbType).c_str(),
              GlobalName::getCatalog(catType).c_str());
  return true;
}

}
