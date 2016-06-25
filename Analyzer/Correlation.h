#include "Common/Global.h"

#include <string>

#pragma once

namespace grb
{

class Catalog;
class ModelBase;

class Correlation
{
public:
  Correlation(type::CorrelationType type = type::CORRELATION_TYPE_UNDEFINED);
  virtual ~Correlation();

  type::CorrelationType getType() const;

  void setXAxis(type::Float range, std::size_t points);
  void setYAxis(type::Float range, std::size_t points);

  virtual bool buildCF(Catalog& catalog) = 0;
  virtual bool saveCF(const std::string& filename) = 0;

protected:
  type::Float _xRange;
  std::size_t _xPoints;
  type::Float _xDelta;

  type::Float _yRange;
  std::size_t _yPoints;
  type::Float _yDelta;

  ModelBase* _model;
private:
  type::CorrelationType _type;


};

}
