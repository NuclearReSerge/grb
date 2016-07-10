#include "Common/Global.h"
#include "Correlation/CorrelationMapper.h"

#include <string>

#pragma once

namespace grb
{

class Catalog;

class Correlation
{
public:
  Correlation(type::CorrelationType type = type::UNDEFINED_CORRELATION);
  virtual ~Correlation();

  type::CorrelationType getType() const;

  void setXAxis(type::Float range, std::size_t points);
  void setYAxis(type::Float range, std::size_t points);

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

}
