#pragma once

namespace grb
{
namespace type
{

enum ValueType
{
  FLAG,
  INTEGER,
  INDEX,
  INTEGER_RANGE,
  INDEX_LIST,
  FLOAT,
  STRING,
  STRING_LIST,

  // LAST
  UNDEFINED_VALUE
};

} // namespace type
} // namespace grb
