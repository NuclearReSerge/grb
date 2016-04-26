#include "Analyzer/GreatCircleDistance.h"

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
GreatCircleDistance::operator()(const Coordinates& p1, const Coordinates& p2)
{
  return (this->*_getDistance)(p1, p2);
}

type::Float
GreatCircleDistance::getSphericalLawOfCosines(const Coordinates& p1, const Coordinates& p2) const
{
  const type::Float phi1 = p1.getLatitude();
  const type::Float phi2 = p2.getLatitude();
  const type::Float dlam = std::abs(p1.getLongnitude() - p2.getLongnitude());

  return std::acos( std::sin(phi1)*std::sin(phi2) + std::cos(phi1)*std::cos(phi2)*std::cos(dlam) );
}

type::Float
GreatCircleDistance::getHaversineFormula(const Coordinates& p1, const Coordinates& p2) const
{
  const type::Float phi1 = p1.getLatitude();
  const type::Float phi2 = p2.getLatitude();
  const type::Float v1 = 0.5 * std::sin(std::abs(phi1 - phi2));
  const type::Float v2 = 0.5 * std::sin(std::abs(p1.getLongnitude() - p2.getLongnitude()));

  return 2.0 * std::asin( v1*v1 + std::cos(phi1)*std::cos(phi2)*v2*v2 );
}

type::Float
GreatCircleDistance::getVinventyFormulae(const Coordinates& p1, const Coordinates& p2) const
{
  const type::Float phi1 = p1.getLatitude();
  const type::Float phi2 = p2.getLatitude();
  const type::Float dlam = std::abs(p1.getLongnitude() - p2.getLongnitude());
  const type::Float v1 = std::cos(phi2)*std::sin(dlam);
  const type::Float v2 = std::cos(phi1)*std::sin(phi2) -
                         std::sin(phi1)*std::cos(phi2)*std::cos(dlam);
  const type::Float v3 = std::sin(phi1)*std::sin(phi2) +
                         std::cos(phi1)*std::cos(phi2)*std::cos(dlam);

  return std::atan2( std::sqrt( v1*v1 + v2*v2 ), v3 );
}

type::Float
GreatCircleDistance::getZero(const Coordinates& p1, const Coordinates& p2) const
{
  return 0.0 * p1.getHorizontal() * p2.getHorizontal();
}

}
