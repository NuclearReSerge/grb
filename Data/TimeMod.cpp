#include "Data/TimeMod.h"

namespace grb
{

namespace
{

// cat grbcatalog.dat | egrep -v "^#" | awk -F "|" '{printf "#%s#%s", $15, $21}' | sed -re "s/\s*(#|$)/\n/g" | sort | uniq | sed "s/^/\ \ \"/g" | sed "s/$/\",/g"

std::vector<std::string> NAME_LIST
{
  "<",
  ">",
  "~"
};

std::string DESCRIPTION = "\
The TXX in literature is not always given as an exact value. This parameter \
records the symbol reported in literature for the approximation (<, >, ~, \
etc.).";
}

TimeModType::TimeModType(const type::ColumnType columnType)
  : NameMapper(columnType)
{
  _description = DESCRIPTION;
  initiate();
}

std::vector<std::string>&
TimeModType::getNameList() const
{
  return NAME_LIST;
}

} // namespace grb


