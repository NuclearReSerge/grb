#include "Database/DatabaseFactory.h"

#include "Database/DatabaseGrbcat.h"

namespace grb
{
namespace factory
{

Database*
DatabaseFactory::createType(const type::DatabaseType& type)
{
  Database* database = nullptr;
  switch (type)
  {
    case type::HEASARC_GRBCAT:
    {
      database = new DatabaseGrbcat;
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
      break;
  }

  if(database)
    database->initialize();

  return database;
}

} // namespace factory
} // namespace grb
