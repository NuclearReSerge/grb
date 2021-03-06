#include "Correlation/GreatCircleDistance.h"
#include "Data/Coordinates.h"

#include <cmath>

namespace grb
{

GreatCircleDistance::GreatCircleDistance(type::ArcFormulaType type)
  : _type(type)
{
  switch (type)
  {
    case type::SPHERICAL_LAW_OF_COSINES:
    {
      _getDistance = &GreatCircleDistance::getSphericalLawOfCosines;
      break;
    }
    case type::HAVERSINE_FORMULA:
    {
      _getDistance = &GreatCircleDistance::getHaversineFormula;
      break;
    }
    case type::VINCENTY_FORMULAE:
    {
      _getDistance = &GreatCircleDistance::getVinventyFormulae;
      break;
    }
    default:
    {
      _getDistance = &GreatCircleDistance::getZero;
    }
  };
}

type::Float
GreatCircleDistance::operator()(Coordinates& p1, Coordinates& p2)
{
  return (this->*_getDistance)(p1, p2);
}

type::Float
GreatCircleDistance::getSphericalLawOfCosines(Coordinates& p1, Coordinates& p2) const
{
  const type::Float phi1 = p1.getCelLatitude();
  const type::Float phi2 = p2.getCelLatitude();
  const type::Float dlam = std::abs(p1.getCelLongnitude() - p2.getCelLongnitude());

  return std::acos( std::sin(phi1)*std::sin(phi2) + std::cos(phi1)*std::cos(phi2)*std::cos(dlam) );
}

type::Float
GreatCircleDistance::getHaversineFormula(Coordinates& p1, Coordinates& p2) const
{
  const type::Float phi1 = p1.getCelLatitude();
  const type::Float phi2 = p2.getCelLatitude();
  const type::Float v1 = std::sin(0.5 * std::abs(phi1 - phi2));
  const type::Float v2 = std::sin(0.5 * std::abs(p1.getCelLongnitude() - p2.getCelLongnitude()));

  return 2.0 * std::asin( std::sqrt(v1*v1 + std::cos(phi1)*std::cos(phi2)*v2*v2) );
}

type::Float
GreatCircleDistance::getVinventyFormulae(Coordinates& p1, Coordinates& p2) const
{
  const type::Float phi1 = p1.getCelLatitude();
  const type::Float phi2 = p2.getCelLatitude();
  const type::Float dlam = std::abs(p1.getCelLongnitude() - p2.getCelLongnitude());
  const type::Float v1 = std::cos(phi2)*std::sin(dlam);
  const type::Float v2 = std::cos(phi1)*std::sin(phi2) -
                         std::sin(phi1)*std::cos(phi2)*std::cos(dlam);
  const type::Float v3 = std::sin(phi1)*std::sin(phi2) +
                         std::cos(phi1)*std::cos(phi2)*std::cos(dlam);

  return std::atan2( std::sqrt( v1*v1 + v2*v2 ), v3 );
}

type::Float
GreatCircleDistance::getZero(Coordinates& p1, Coordinates& p2) const
{
  return 0.0 * p1.getCarX() * p2.getCarX();
}

} // namespace grb
