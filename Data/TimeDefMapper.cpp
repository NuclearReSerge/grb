#include "Data/TimeDefMapper.h"

namespace
{

// cat grbcatalog.dat | egrep -v "^#" | awk -F "|" '{print $13}' | sed "s/\s*$//g" | sed "s/-/\ /g" | sed "s/\.$//g" | sed "s/r\ T/r\ t/g" | sed "s/t\ S/t\ s/g" |sort | uniq | sed "s/^/\ \ \"/g"| sed "s/$/\",/g"

const std::vector<std::string> NAME_LIST
{
  "BAT trigger",
  "Earth Crossing Time",
  "Not Specified",
  "Time at CGRO (or BATSE)",
  "Time at Detecting Instrument",
  "Time at Watch/GRANAT",
  "Trigger Time"
};

const std::string DESCRIPTION = "\
The time of a GRB occurrence has different definition depending on how has been detected. This \
field records a string related to the method of detection.";

} // namespace

namespace grb
{
namespace mapper
{

const std::string&
TimeDefMapper::getDescription() const
{
  return DESCRIPTION;
}

const std::vector<std::string>&
TimeDefMapper::getList() const
{
  return NAME_LIST;
}

} // namespace mapper
} // namespace grb
