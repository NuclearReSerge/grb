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
  addColumn(new DataBaseColumn(type::RECORD_NUMBER,  type::NO_UNIT,  type::INTEGER,       true ));
  addColumn(new DataBaseColumn(type::ID,             type::NO_UNIT,  type::INTEGER,       true ));
  addColumn(new DataBaseColumn(type::NAME,           type::NO_UNIT,  type::STRING,        true ));
  addColumn(new DataBaseColumn(type::ALT_NAMES,      type::NO_UNIT,  type::STRING_LIST,   false));
  addColumn(new DataBaseColumn(type::TIME,           type::UNIT_MJD, type::FLOAT,         true ));
  addColumn(new DataBaseColumn(type::TIME_DEF,       type::NO_UNIT,  type::INDEX,         true ));
  addColumn(new DataBaseColumn(type::OBSERVATORY,    type::NO_UNIT,  type::INDEX,         true ));
  addColumn(new DataBaseColumn(type::COORD_RA,       type::DEGREE,   type::FLOAT,         false));
  addColumn(new DataBaseColumn(type::COORD_DEC,      type::DEGREE,   type::FLOAT,         false));
  addColumn(new DataBaseColumn(type::COORD_FLAG,     type::NO_UNIT,  type::FLOAT,         true ));
  addColumn(new DataBaseColumn(type::REGION,         type::NO_UNIT,  type::INDEX,         false));
  addColumn(new DataBaseColumn(type::AFTERGLOW_FLAG, type::NO_UNIT,  type::FLAG,          true ));
  addColumn(new DataBaseColumn(type::REFERENCE,      type::NO_UNIT,  type::INDEX_LIST,    false));
  addColumn(new DataBaseColumn(type::T50_MOD,        type::NO_UNIT,  type::INDEX,         false));
  addColumn(new DataBaseColumn(type::T50,            type::SECOND,   type::FLOAT,         false));
  addColumn(new DataBaseColumn(type::T50_ERROR,      type::SECOND,   type::FLOAT,         false));
  addColumn(new DataBaseColumn(type::T50_RANGE,      type::NO_UNIT,  type::INTEGER_RANGE, false));
  addColumn(new DataBaseColumn(type::T50_EMIN,       type::KILO_EV,  type::INTEGER,       false));
  addColumn(new DataBaseColumn(type::T50_EMAX,       type::KILO_EV,  type::INTEGER,       false));
  addColumn(new DataBaseColumn(type::T90_MOD,        type::NO_UNIT,  type::INDEX,         false));
  addColumn(new DataBaseColumn(type::T90,            type::SECOND,   type::FLOAT,         false));
  addColumn(new DataBaseColumn(type::T90_ERROR,      type::SECOND,   type::FLOAT,         false));
  addColumn(new DataBaseColumn(type::T90_RANGE,      type::NO_UNIT,  type::INTEGER_RANGE, false));
  addColumn(new DataBaseColumn(type::T90_EMIN,       type::KILO_EV,  type::INTEGER,       false));
  addColumn(new DataBaseColumn(type::T90_EMAX,       type::KILO_EV,  type::INTEGER,       false));
  addColumn(new DataBaseColumn(type::T_OTHER,        type::SECOND,   type::FLOAT,         false));
  addColumn(new DataBaseColumn(type::FLUX_FLAG,      type::NO_UNIT,  type::FLAG,          true ));
  addColumn(new DataBaseColumn(type::NOTES,          type::NO_UNIT,  type::STRING,        false));
  addColumn(new DataBaseColumn(type::FLUX_NOTES,     type::NO_UNIT,  type::STRING,        false));
  addColumn(new DataBaseColumn(type::LOCAL_NOTES,    type::NO_UNIT,  type::STRING,        false));
  addColumn(new DataBaseColumn(type::CLASS,          type::NO_UNIT,  type::INTEGER,       false));

  setColumnFlags();
}

} // namespace grb
