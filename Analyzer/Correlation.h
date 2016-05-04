#pragma once

namespace grb
{

namespace type
{

enum CorrelationType
{
  TIME_DIFF_VS_CIRCLE_DIST_GRBCAT,

  // LAST
  UNKNOWN_CORRELATION_TYPE
};

}

class Catalog;

class Correlation
{
public:
  Correlation(type::CorrelationType type = type::UNKNOWN_CORRELATION_TYPE);
  virtual ~Correlation();

  type::CorrelationType getType() const;

  virtual bool buildCF(const Catalog& catalog) = 0;

private:
  type::CorrelationType _type;
};

}
