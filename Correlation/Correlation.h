#pragma once

#include "Common/BaseObject.h"
#include "Common/Global.h"
#include "Correlation/CorrelationCmdType.h"
#include "Correlation/CorrelationType.h"

#include <cmath>
#include <list>
#include <string>

namespace grb
{

typedef BaseObject<type::CorrelationType, type::CorrelationCmdType> CorrelationBase;

class Catalog;

class Correlation : public CorrelationBase
{
public:
  Correlation(type::CorrelationType type = type::UNDEFINED_CORRELATION)
  : CorrelationBase(type), _configured(false),
    _xRange(1.0), _xPoints(0), _xDelta(0.0),
    _yRange(1.0), _yPoints(0), _yDelta(0.0)
  {
  }

  bool isConfigured() const
  {
    return _configured && _xPoints && _yPoints;
  }

  void setConfigured(const bool configured = true)
  {
    _configured = configured;
  }

  type::Float getXRange() const { return _xRange; }
  std::size_t getXPoints() const { return _xPoints; }
  type::Float getXDelta() const { return _xDelta; }

  type::Float getYRange() const { return _yRange; }
  std::size_t getYPoints() const { return _yPoints; }
  type::Float getYDelta() const { return _yDelta; }

  void generate(Catalog& catalogData, Catalog& catalogModel)
  {
    doGenerate(catalogData, catalogModel);
  }

protected:
  virtual void doGenerate(Catalog& catalogData, Catalog& catalogModel) = 0;

  bool isCommandValid(type::CorrelationCmdType cmd)
  {
    switch (cmd)
    {
      case type::CORRELATION_CREATE:
      case type::CORRELATION_GENERATE:
      case type::CORRELATION_HELP:
      {
        return false;
      }
      default:
        return true;;
    }
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

private:
  bool _configured;

  type::Float _xRange;
  std::size_t _xPoints;
  type::Float _xDelta;

  type::Float _yRange;
  std::size_t _yPoints;
  type::Float _yDelta;
};

} // namespace grb
