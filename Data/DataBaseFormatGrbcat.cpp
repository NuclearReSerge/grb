#include "Data/DataBaseFormatGrbcat.h"

#include "Data/DataType.h"

namespace grb
{

DataBaseFormatGrbcat::DataBaseFormatGrbcat(const type::DatabaseTableType dbType)
  : DataBaseFormat(dbType)
{
  _coordSys = type::J2000;
}

/***************************************************************************************************
 *
 * default_search_radius = 60
 * table_author = Angelini et al.
 *
 **************************************************************************************************/
void
DataBaseFormatGrbcat::initialize() throw(Exception)
{
  _format.push_back(new DataType(type::RECORD_NUMBER,  true,  type::NO_UNIT, type::INTEGER));
  _format.push_back(new DataType(type::ID,             true,  type::NO_UNIT, type::INTEGER));
  _format.push_back(new DataType(type::NAME,           true,  type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::ALT_NAMES,      false, type::NO_UNIT, type::STRING_LIST));
  _format.push_back(new DataType(type::TIME,           true,  type::MJD,     type::FLOAT));
  _format.push_back(new DataType(type::TIME_DEF,       true,  type::NO_UNIT, type::INDEX));
  _format.push_back(new DataType(type::OBSERVATORY,    true,  type::NO_UNIT, type::INDEX));
  _format.push_back(new DataType(type::COORD_RA,       false, type::DEGREE,  type::FLOAT));
  _format.push_back(new DataType(type::COORD_DEC,      false, type::DEGREE,  type::FLOAT));
  _format.push_back(new DataType(type::COORD_FLAG,     true,  type::NO_UNIT, type::FLOAT));
  _format.push_back(new DataType(type::REGION,         false, type::NO_UNIT, type::INDEX));
  _format.push_back(new DataType(type::AFTERGLOW_FLAG, true,  type::NO_UNIT, type::FLAG));
  _format.push_back(new DataType(type::REFERENCE,      true,  type::NO_UNIT, type::INDEX_LIST));
  _format.push_back(new DataType(type::T50_MOD,        false, type::NO_UNIT, type::INDEX));
  _format.push_back(new DataType(type::T50,            false, type::SECOND,  type::FLOAT));
  _format.push_back(new DataType(type::T50_ERROR,      false, type::SECOND,  type::FLOAT));
  _format.push_back(new DataType(type::T50_RANGE,      false, type::NO_UNIT, type::INTEGER_RANGE));
  _format.push_back(new DataType(type::T50_EMIN,       false, type::KILO_EV, type::INTEGER));
  _format.push_back(new DataType(type::T50_EMAX,       false, type::KILO_EV, type::INTEGER));
  _format.push_back(new DataType(type::T90_MOD,        false, type::NO_UNIT, type::INDEX));
  _format.push_back(new DataType(type::T90,            false, type::SECOND,  type::FLOAT));
  _format.push_back(new DataType(type::T90_ERROR,      false, type::SECOND,  type::FLOAT));
  _format.push_back(new DataType(type::T90_RANGE,      false, type::NO_UNIT, type::INTEGER_RANGE));
  _format.push_back(new DataType(type::T90_EMIN,       false, type::KILO_EV, type::INTEGER));
  _format.push_back(new DataType(type::T90_EMAX,       false, type::KILO_EV, type::INTEGER));
  _format.push_back(new DataType(type::T_OTHER,        false, type::SECOND,  type::FLOAT));
  _format.push_back(new DataType(type::FLUX_FLAG,      true,  type::NO_UNIT, type::FLAG));
  _format.push_back(new DataType(type::NOTES,          false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::FLUX_NOTES,     false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::LOCAL_NOTES,    false, type::NO_UNIT, type::STRING));
  _format.push_back(new DataType(type::CLASS,          false, type::NO_UNIT, type::INTEGER));
  _format.push_back(new DataType(type::DUMMY,          false, type::NO_UNIT, type::STRING));

  setupRequiredColumns();
}

}
