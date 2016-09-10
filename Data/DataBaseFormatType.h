#pragma once

namespace grb
{
namespace type
{

// High Energy Astrophysics Science Archive Research Center
// http://heasarc.gsfc.nasa.gov/
enum DatabaseFormatType
{
  // HEASARC
  HEASARC_GRBCAT,
  HEASARC_GRBCATAG,
  HEASARC_GRBCATANN,
  HEASARC_GRBCATBOX,
  HEASARC_GRBCATCIRC,
  HEASARC_GRBCATDUAL,
  HEASARC_GRBCATFLUX,
  HEASARC_GRBCATINT,
  HEASARC_GRBCATINTA,
  HEASARC_GRBCATIRR,

  // TEST
  TEST_DATABASE_TABLE,
  // LAST
  UNDEFINED_DATABASE_TABLE
};

} // namespace type
} // namespace grb
