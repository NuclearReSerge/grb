#include "Analyzer/Correlation.h"

namespace grb
{

Correlation::Correlation(type::CorrelationType type)
  : _xRange(0.0), _xPoints(0), _xDelta(0.0), _yRange(0.0), _yPoints(0), _yDelta(0.0),
    _type(type)
{

}

Correlation::~Correlation()
{

}

type::CorrelationType
Correlation::getType() const
{
  return _type;
}

void
Correlation::setXAxis(type::Float range, std::size_t points)
{
  _xRange = range;
  _xPoints = points;
  _xDelta = _xPoints / _xRange;
}

void
Correlation::setYAxis(type::Float range, std::size_t points)
{
  _yRange = range;
  _yPoints = points;
  _yDelta = _yPoints / _yRange;
}


}
