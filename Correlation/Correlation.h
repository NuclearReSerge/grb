#include "Common/Global.h"
#include "Correlation/CorrelationType.h"

#include <cmath>
#include <list>
#include <string>

#pragma once

namespace grb
{

class Catalog;

class Correlation
{
public:
  Correlation(type::CorrelationType type = type::UNDEFINED_CORRELATION)
  : _xRange(1.0), _xPoints(0), _xDelta(0.0), _yRange(1.0), _yPoints(0), _yDelta(0.0),
    _type(type)
  {
  }

  virtual ~Correlation() = default;

  type::CorrelationType getType() const
  {
    return _type;
  }

  bool setXAxis(type::Float range, std::size_t points)
  {
    if (std::fpclassify(range) == FP_ZERO )
      return false;

    _xRange = range;
    _xPoints = points;
    _xDelta = _xPoints / _xRange;
    return true;
  }

  bool setYAxis(type::Float range, std::size_t points)
  {
    if (std::fpclassify(range) == FP_ZERO )
      return false;

    _yRange = range;
    _yPoints = points;
    _yDelta = _yPoints / _yRange;
    return true;
  }

  type::Float getXRange() const { return _xRange; }
  std::size_t getXPoints() const { return _xPoints; }
  type::Float getXDelta() const { return _xDelta; }

  type::Float getYRange() const { return _yRange; }
  std::size_t getYPoints() const { return _yPoints; }
  type::Float getYDelta() const { return _yDelta; }

  virtual bool parse(std::list<std::string>& tokens) = 0;
  virtual bool build(Catalog& catalogData, Catalog& catalogModel) = 0;
  virtual bool save(const std::string& filePrefix) = 0;

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
