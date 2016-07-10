#include "Data/DataBaseFormatFactory.h"

#include "Data/DataBaseFormatGrbcat.h"

namespace grb
{

namespace factory
{

DataBaseFormat*
DataBaseFormatFactory::create(type::DatabaseTableType type)
{
  DataBaseFormat* format = nullptr;
  switch (type)
  {
    case type::HEASARC_GRBCAT:
    {
      format = new DataBaseFormatGrbcat;
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

  if(format)
    format->initialize();

  return format;
}

DataBaseFormat*
DataBaseFormatFactory::create(const std::string& name)
{
  type::DatabaseTableType type;
  try
  {
    type = DataBaseFormatMapper::instance()->getValue(name);
  }
  catch (Exception& exc)
  {
    return nullptr;
  }
  return create(type);
}

}

}
