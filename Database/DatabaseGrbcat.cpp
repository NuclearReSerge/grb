#include "Database/DatabaseGrbcat.h"

namespace grb
{

/***************************************************************************************************
 *
 * default_search_radius = 60
 * table_author = Angelini et al.
 *
 **************************************************************************************************/
void
DatabaseGrbcat::initialize()
{
  addColumn(new DatabaseColumn(type::RECORD_NUMBER,  type::NO_UNIT,  type::INTEGER,       true ));
  addColumn(new DatabaseColumn(type::ID,             type::NO_UNIT,  type::INTEGER,       true ));
  addColumn(new DatabaseColumn(type::NAME,           type::NO_UNIT,  type::STRING,        true ));
  addColumn(new DatabaseColumn(type::ALT_NAMES,      type::NO_UNIT,  type::STRING_LIST,   false));
  addColumn(new DatabaseColumn(type::TIME,           type::UNIT_MJD, type::FLOAT,         true ));
  addColumn(new DatabaseColumn(type::TIME_DEF,       type::NO_UNIT,  type::INDEX,         true ));
  addColumn(new DatabaseColumn(type::OBSERVATORY,    type::NO_UNIT,  type::INDEX,         true ));
  addColumn(new DatabaseColumn(type::COORD_RA,       type::DEGREE,   type::FLOAT,         false));
  addColumn(new DatabaseColumn(type::COORD_DEC,      type::DEGREE,   type::FLOAT,         false));
  addColumn(new DatabaseColumn(type::COORD_FLAG,     type::NO_UNIT,  type::FLOAT,         true ));
  addColumn(new DatabaseColumn(type::REGION,         type::NO_UNIT,  type::INDEX,         false));
  addColumn(new DatabaseColumn(type::AFTERGLOW_FLAG, type::NO_UNIT,  type::FLAG,          true ));
  addColumn(new DatabaseColumn(type::REFERENCE,      type::NO_UNIT,  type::INDEX_LIST,    false));
  addColumn(new DatabaseColumn(type::T50_MOD,        type::NO_UNIT,  type::INDEX,         false));
  addColumn(new DatabaseColumn(type::T50,            type::SECOND,   type::FLOAT,         false));
  addColumn(new DatabaseColumn(type::T50_ERROR,      type::SECOND,   type::FLOAT,         false));
  addColumn(new DatabaseColumn(type::T50_RANGE,      type::NO_UNIT,  type::INTEGER_RANGE, false));
  addColumn(new DatabaseColumn(type::T50_EMIN,       type::KILO_EV,  type::INTEGER,       false));
  addColumn(new DatabaseColumn(type::T50_EMAX,       type::KILO_EV,  type::INTEGER,       false));
  addColumn(new DatabaseColumn(type::T90_MOD,        type::NO_UNIT,  type::INDEX,         false));
  addColumn(new DatabaseColumn(type::T90,            type::SECOND,   type::FLOAT,         false));
  addColumn(new DatabaseColumn(type::T90_ERROR,      type::SECOND,   type::FLOAT,         false));
  addColumn(new DatabaseColumn(type::T90_RANGE,      type::NO_UNIT,  type::INTEGER_RANGE, false));
  addColumn(new DatabaseColumn(type::T90_EMIN,       type::KILO_EV,  type::INTEGER,       false));
  addColumn(new DatabaseColumn(type::T90_EMAX,       type::KILO_EV,  type::INTEGER,       false));
  addColumn(new DatabaseColumn(type::T_OTHER,        type::SECOND,   type::FLOAT,         false));
  addColumn(new DatabaseColumn(type::FLUX_FLAG,      type::NO_UNIT,  type::FLAG,          true ));
  addColumn(new DatabaseColumn(type::NOTES,          type::NO_UNIT,  type::STRING,        false));
  addColumn(new DatabaseColumn(type::FLUX_NOTES,     type::NO_UNIT,  type::STRING,        false));
  addColumn(new DatabaseColumn(type::LOCAL_NOTES,    type::NO_UNIT,  type::STRING,        false));
  addColumn(new DatabaseColumn(type::CLASS,          type::NO_UNIT,  type::INTEGER,       false));

  setColumnFlags();
}

bool
DatabaseGrbcat::doParse(type::DatabaseCmdType cmd, std::list<std::string>& tokens)
{
  switch (cmd)
  {
    default:
      break;
  }

  tokens.clear();

  return true;
}

void
DatabaseGrbcat::doExecute(type::DatabaseCmdType cmd)
{
  switch (cmd)
  {
    default:
      break;
  }
}

std::string
DatabaseGrbcat::doHelp()
{
  return "DatabaseGrbcat::doHelp";
}

} // namespace grb
