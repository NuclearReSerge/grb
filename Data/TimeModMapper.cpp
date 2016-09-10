#include "Data/TimeModMapper.h"

namespace
{

// cat grbcatalog.dat | egrep -v "^#" | awk -F "|" '{printf "#%s#%s", $15, $21}' | sed -re "s/\s*(#|$)/\n/g" | sort | uniq | sed "s/^/\ \ \"/g" | sed "s/$/\",/g"
const std::vector<std::string> NAME_LIST
{
  "<",
  ">",
  "~"
};

const std::string DESCRIPTION = "\
The TXX in literature is not always given as an exact value. This parameter records the symbol \
reported in literature for the approximation (<, >, ~, etc.).";

} // namespace

namespace grb
{
namespace mapper
{

const std::string&
Time50ModMapper::getDescription() const
{
  return DESCRIPTION;
}
const std::vector<std::string>&
Time50ModMapper::getList() const
{
  return NAME_LIST;
}

const std::string&
Time90ModMapper::getDescription() const
{
  return DESCRIPTION;
}
const std::vector<std::string>&
Time90ModMapper::getList() const
{
  return NAME_LIST;
}


} // namespace mapper
} // namespace grb


