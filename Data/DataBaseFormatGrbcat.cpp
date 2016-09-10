#include "Data/DataBaseFormatGrbcat.h"

namespace grb
{

/***************************************************************************************************
 *
 * default_search_radius = 60
 * table_author = Angelini et al.
 *
 **************************************************************************************************/
void
DataBaseFormatGrbcat::initialize()
{
  addColumn(new DataBaseColumn(type::RECORD_NUMBER,  true,  type::NO_UNIT,  type::INTEGER));
  addColumn(new DataBaseColumn(type::ID,             true,  type::NO_UNIT,  type::INTEGER));
  addColumn(new DataBaseColumn(type::NAME,           true,  type::NO_UNIT,  type::STRING));
  addColumn(new DataBaseColumn(type::ALT_NAMES,      false, type::NO_UNIT,  type::STRING_LIST));
  addColumn(new DataBaseColumn(type::TIME,           true,  type::UNIT_MJD, type::FLOAT));
  addColumn(new DataBaseColumn(type::TIME_DEF,       true,  type::NO_UNIT,  type::INDEX));
  addColumn(new DataBaseColumn(type::OBSERVATORY,    true,  type::NO_UNIT,  type::INDEX));
  addColumn(new DataBaseColumn(type::COORD_RA,       false, type::DEGREE,   type::FLOAT));
  addColumn(new DataBaseColumn(type::COORD_DEC,      false, type::DEGREE,   type::FLOAT));
  addColumn(new DataBaseColumn(type::COORD_FLAG,     true,  type::NO_UNIT,  type::FLOAT));
  addColumn(new DataBaseColumn(type::REGION,         false, type::NO_UNIT,  type::INDEX));
  addColumn(new DataBaseColumn(type::AFTERGLOW_FLAG, true,  type::NO_UNIT,  type::FLAG));
  addColumn(new DataBaseColumn(type::REFERENCE,      false, type::NO_UNIT,  type::INDEX_LIST));
  addColumn(new DataBaseColumn(type::T50_MOD,        false, type::NO_UNIT,  type::INDEX));
  addColumn(new DataBaseColumn(type::T50,            false, type::SECOND,   type::FLOAT));
  addColumn(new DataBaseColumn(type::T50_ERROR,      false, type::SECOND,   type::FLOAT));
  addColumn(new DataBaseColumn(type::T50_RANGE,      false, type::NO_UNIT,  type::INTEGER_RANGE));
  addColumn(new DataBaseColumn(type::T50_EMIN,       false, type::KILO_EV,  type::INTEGER));
  addColumn(new DataBaseColumn(type::T50_EMAX,       false, type::KILO_EV,  type::INTEGER));
  addColumn(new DataBaseColumn(type::T90_MOD,        false, type::NO_UNIT,  type::INDEX));
  addColumn(new DataBaseColumn(type::T90,            false, type::SECOND,   type::FLOAT));
  addColumn(new DataBaseColumn(type::T90_ERROR,      false, type::SECOND,   type::FLOAT));
  addColumn(new DataBaseColumn(type::T90_RANGE,      false, type::NO_UNIT,  type::INTEGER_RANGE));
  addColumn(new DataBaseColumn(type::T90_EMIN,       false, type::KILO_EV,  type::INTEGER));
  addColumn(new DataBaseColumn(type::T90_EMAX,       false, type::KILO_EV,  type::INTEGER));
  addColumn(new DataBaseColumn(type::T_OTHER,        false, type::SECOND,   type::FLOAT));
  addColumn(new DataBaseColumn(type::FLUX_FLAG,      true,  type::NO_UNIT,  type::FLAG));
  addColumn(new DataBaseColumn(type::NOTES,          false, type::NO_UNIT,  type::STRING));
  addColumn(new DataBaseColumn(type::FLUX_NOTES,     false, type::NO_UNIT,  type::STRING));
  addColumn(new DataBaseColumn(type::LOCAL_NOTES,    false, type::NO_UNIT,  type::STRING));
  addColumn(new DataBaseColumn(type::CLASS,          false, type::NO_UNIT,  type::INTEGER));

  setColumnFlags();
}

} // namespace grb
