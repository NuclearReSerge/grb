#include "Data/DataBaseFormatGrbcat.h"

namespace grb
{

DataBaseFormatGrbcat::DataBaseFormatGrbcat()
  : DataBaseFormat(type::HEASARC_GRBCAT), _coordSys(type::EQUATORIAL_J2000)
{
}

type::CoordinateSystemType
DataBaseFormatGrbcat::getCoordinateSystem() const
{
  return _coordSys;
}

/***************************************************************************************************
 *
 * default_search_radius = 60
 * table_author = Angelini et al.
 *
 **************************************************************************************************/
void
DataBaseFormatGrbcat::initialize()
{
  addDataType(new DataType(type::RECORD_NUMBER,  true,  type::NO_UNIT,  type::INTEGER));
  addDataType(new DataType(type::ID,             true,  type::NO_UNIT,  type::INTEGER));
  addDataType(new DataType(type::NAME,           true,  type::NO_UNIT,  type::STRING));
  addDataType(new DataType(type::ALT_NAMES,      false, type::NO_UNIT,  type::STRING_LIST));
  addDataType(new DataType(type::TIME,           true,  type::UNIT_MJD, type::FLOAT));
  addDataType(new DataType(type::TIME_DEF,       true,  type::NO_UNIT,  type::INDEX));
  addDataType(new DataType(type::OBSERVATORY,    true,  type::NO_UNIT,  type::INDEX));
  addDataType(new DataType(type::COORD_RA,       false, type::DEGREE,   type::FLOAT));
  addDataType(new DataType(type::COORD_DEC,      false, type::DEGREE,   type::FLOAT));
  addDataType(new DataType(type::COORD_FLAG,     true,  type::NO_UNIT,  type::FLOAT));
  addDataType(new DataType(type::REGION,         false, type::NO_UNIT,  type::INDEX));
  addDataType(new DataType(type::AFTERGLOW_FLAG, true,  type::NO_UNIT,  type::FLAG));
  addDataType(new DataType(type::REFERENCE,      false, type::NO_UNIT,  type::INDEX_LIST));
  addDataType(new DataType(type::T50_MOD,        false, type::NO_UNIT,  type::INDEX));
  addDataType(new DataType(type::T50,            false, type::SECOND,   type::FLOAT));
  addDataType(new DataType(type::T50_ERROR,      false, type::SECOND,   type::FLOAT));
  addDataType(new DataType(type::T50_RANGE,      false, type::NO_UNIT,  type::INTEGER_RANGE));
  addDataType(new DataType(type::T50_EMIN,       false, type::KILO_EV,  type::INTEGER));
  addDataType(new DataType(type::T50_EMAX,       false, type::KILO_EV,  type::INTEGER));
  addDataType(new DataType(type::T90_MOD,        false, type::NO_UNIT,  type::INDEX));
  addDataType(new DataType(type::T90,            false, type::SECOND,   type::FLOAT));
  addDataType(new DataType(type::T90_ERROR,      false, type::SECOND,   type::FLOAT));
  addDataType(new DataType(type::T90_RANGE,      false, type::NO_UNIT,  type::INTEGER_RANGE));
  addDataType(new DataType(type::T90_EMIN,       false, type::KILO_EV,  type::INTEGER));
  addDataType(new DataType(type::T90_EMAX,       false, type::KILO_EV,  type::INTEGER));
  addDataType(new DataType(type::T_OTHER,        false, type::SECOND,   type::FLOAT));
  addDataType(new DataType(type::FLUX_FLAG,      true,  type::NO_UNIT,  type::FLAG));
  addDataType(new DataType(type::NOTES,          false, type::NO_UNIT,  type::STRING));
  addDataType(new DataType(type::FLUX_NOTES,     false, type::NO_UNIT,  type::STRING));
  addDataType(new DataType(type::LOCAL_NOTES,    false, type::NO_UNIT,  type::STRING));
  addDataType(new DataType(type::CLASS,          false, type::NO_UNIT,  type::INTEGER));

  setColumnFlags();
}

}
