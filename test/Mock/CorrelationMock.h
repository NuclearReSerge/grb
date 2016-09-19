#include "Correlation/Correlation.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class CorrelationMock : public Correlation
{
public:
  CorrelationMock()
    : Correlation()
  {
  }

  type::Float getxRange() const { return _xRange; }
  std::size_t getxPoints() const { return _xPoints; }
  type::Float getxDelta() const { return _xDelta; }

  type::Float getyRange() const { return _yRange; }
  std::size_t getyPoints() const { return _yPoints; }
  type::Float getyDelta() const { return _yDelta; }

  MOCK_METHOD2(buildCF, bool(Catalog& catalogData, Catalog& catalogModel));
  MOCK_METHOD1(saveCF, bool(const std::string& filename));
};

} // namespace grb
