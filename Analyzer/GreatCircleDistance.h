#include "Common/Global.h"
#include "Data/Coordinates.h"

#pragma once

namespace grb
{

namespace type
{

enum ArcFormulaType
{
  SPHERICAL_LAW_OF_COSINES,
  HAVERSINE_FORMULA,
  VINCENTY_FORMULAE,

  UNKNOWN_ARC_FORMULA_TYPE
};

}

class GreatCircleDistance
{
public:
  GreatCircleDistance(type::ArcFormulaType type = type::VINCENTY_FORMULAE);

  type::Float operator()(Coordinates& pA, Coordinates& p2);

protected:
// \Delta\sigma=\arccos\bigl(\sin\phi_1\cdot\sin\phi_2+\cos\phi_1\cdot\cos\phi_2\cdot\cos(\Delta\lambda)\bigr)
  type::Float getSphericalLawOfCosines(Coordinates& pA, Coordinates& p2) const;
// \Delta\sigma=2\arcsin \sqrt{\sin^2\left(\frac{\Delta\phi}{2}\right)+\cos{\phi_1}\cdot\cos{\phi_2}\cdot\sin^2\left(\frac{\Delta\lambda}{2}\right)}
  type::Float getHaversineFormula(Coordinates& pA, Coordinates& p2) const;
// \Delta\sigma=\arctan \frac{\sqrt{\left(\cos\phi_2\cdot\sin(\Delta\lambda)\right)^2+\left(\cos\phi_1\cdot\sin\phi_2-\sin\phi_1\cdot\cos\phi_2\cdot\cos(\Delta\lambda)\right)^2}}{\sin\phi_1\cdot\sin\phi_2+\cos\phi_1\cdot\cos\phi_2\cdot\cos(\Delta\lambda)}
  type::Float getVinventyFormulae(Coordinates& pA, Coordinates& p2) const;
// \Delta\sigma=0
  type::Float getZero(Coordinates& pA, Coordinates& p2) const;

private:

  type::Float (GreatCircleDistance::*_getDistance)(Coordinates& pA, Coordinates& p2) const;
  type::ArcFormulaType _type;
};

}
