#include "Common/Global.h"

#pragma once

namespace grb
{


class Coordinates
{
public:
  Coordinates(type::CoordinateSystemType type = type::COORDINATE_SYSTEM_UNDEFINED);

  type::CoordinateSystemType getType() const;

  const type::Float& getCoordFlag() const;
// undefined coordinate system or based on type
  const type::Float& getHorizontal() const;
  const type::Float& getVertical() const;
// equinox J2000
  const type::Float& getRightAscension() const;
  const type::Float& getDeclination() const;
// galactic
  const type::Float& getLongnitude() const;
  const type::Float& getLatitude() const;

protected:
  friend class CatalogEntryGRBCAT;
  type::Float& getCoordFlag();
  type::Float& getHorizontal();
  type::Float& getVertical();

  void setHorizontalUnitType(type::UnitType unitType);
  void setVerticalUnitType(type::UnitType unitType);

  bool isValid();

private:
  type::CoordinateSystemType _type;
  type::Float _coord_flag;
  type::Float _horizontal;
  type::Float _vertical;
  type::UnitType _horizontalUnitType;
  type::UnitType _verticalUnitType;
};

}
