#include "Common/Global.h"
#include "Correlation/CorrelationType.h"

#include <string>

#pragma once

namespace grb
{

class Catalog;

class Correlation
{
public:
  Correlation(type::CorrelationType type = type::UNDEFINED_CORRELATION)
  : _xRange(0.0), _xPoints(0), _xDelta(0.0), _yRange(0.0), _yPoints(0), _yDelta(0.0),
    _type(type)
  {
  }

  virtual ~Correlation() = default;

  type::CorrelationType getType() const
  {
    return _type;
  }

  void setXAxis(type::Float range, std::size_t points)
  {
    _xRange = range;
    _xPoints = points;
    _xDelta = _xPoints / _xRange;
  }

  void setYAxis(type::Float range, std::size_t points)
  {
    _yRange = range;
    _yPoints = points;
    _yDelta = _yPoints / _yRange;
  }

  virtual bool buildCF(Catalog& catalogData, Catalog& catalogModel) = 0;
  virtual bool saveCF(const std::string& filename) = 0;

protected:
  type::Float _xRange;
  std::size_t _xPoints;
  type::Float _xDelta;

  type::Float _yRange;
  std::size_t _yPoints;
  type::Float _yDelta;

private:
  type::CorrelationType _type;
};

} // namespace grb
