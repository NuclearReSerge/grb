#pragma once

#include <cstdlib>

namespace grb
{

class Parser
{
public:
  Parser() = default;
  virtual ~Parser() = default;

  virtual bool parse() = 0;

  std::size_t getNumberOfRows() const
  {
    return _rows;
  }

protected:
  std::size_t _rows = 0;
};

} // namespace grb
