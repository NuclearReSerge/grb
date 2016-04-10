#include "Data/Region.h"

namespace grb
{

namespace
{

// cat grbcatalog.dat | egrep -v "^#" | awk -F "|" '{print $7}' | sed "s/\s*$//g" | sort | uniq | sed "s/^/\ \ \"/g" | sed "s/$/\",/g"

const std::vector<std::string> NAME_LIST
{
  "annulus",
  "annulus_int",
  "box",
  "circle",
  "dual",
  "intersect",
  "irregular"
};

const std::string DESCRIPTION = "\
This parameter contains the name of the region. The possible regions are: circle, annulus, box, \
dual, annulus intersect, irregular, intersect.";
}

RegionType::RegionType()
  : NameMapper(type::REGION, DESCRIPTION)
{
  initiate();
}

const std::vector<std::string>& RegionType::getNameList() const
{
  return NAME_LIST;
}

} // namespace grb
