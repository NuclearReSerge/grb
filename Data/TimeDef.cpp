#include "Data/TimeDef.h"

namespace grb
{

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
}

TimeDefType::TimeDefType()
  : NameMapper(type::TIME_DEF, DESCRIPTION)
{
  initiate();
}

const std::vector<std::string>& TimeDefType::getNameList() const
{
  return NAME_LIST;
}

} // namespace grb
