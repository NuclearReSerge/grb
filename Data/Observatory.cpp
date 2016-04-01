#include "Data/Observatory.h"

namespace grb
{

namespace
{

// cat grbcatalog.dat | egrep -v "^#" | awk -F "|" '{print $3}' | sed "s/\s*$//g" | sort | uniq | sed "s/^/\ \ \"/g" | sed "s/$/\",/g"

const NameMapper::VectorString NAME_LIST
{
  "APEX",
  "BATSE-CGRO",
  "BeppoSAX",
  "CATALOG",
  "CGRO/MO/ULYSSES",
  "COMPTEL-CGRO",
  "DMSP",
  "GRS-SMM",
  "HELICON-CORONASF",
  "HETE2",
  "HINOTORI",
  "INTEGRAL",
  "IPN",
  "IPN/HETE2",
  "IPN/INTEGRAL",
  "IPN/ULYSSES/BeppoSAX",
  "IPN/WATCH",
  "IPN/WXM-HETE2",
  "KONUS-WIND",
  "KONUS-WIND/HELICON-CORONASF",
  "KONUS-WIND/VENERA 13 or 14",
  "PHEBUS-GRANAT",
  "PVO",
  "PVO/CGRO/ULYSSES",
  "SIGMA-GRANAT",
  "SIGNE 2m/PROGNOZ7",
  "SIGNE 2m/VENERA 11",
  "SIGNE 2m/VENERA 12",
  "SWIFT",
  "SXC-HETE2",
  "ULYSSES",
  "ULYSSES/BATSE-CGRO",
  "ULYSSES/KONUS-WIND",
  "VELA",
  "WATCH-GRANAT",
  "WXM-HETE2"
};

const std::string DESCRIPTION = "\
Name of the observatory that detected the burst. If the observatory has more than one instrument \
capable of detecting GRB, this is reported with the following convention 'observatory-instrument'. \
If the detection of a GRB was determined by the contribution of different observatories, this is \
reported using the following convention 'observatory1/observatory2/...'.";
}

ObservatoryType::ObservatoryType()
  : NameMapper(type::OBSERVATORY, DESCRIPTION)
{
  initiate();
}

const NameMapper::VectorString&
ObservatoryType::getNameList() const
{
  return NAME_LIST;
}

} // namespace grb
