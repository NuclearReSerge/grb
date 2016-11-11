#pragma once

namespace grb
{
namespace type
{

// High Energy Astrophysics Science Archive Research Center
// http://heasarc.gsfc.nasa.gov/
enum DatabaseType
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

  // LAST
  UNDEFINED_DATABASE
};

} // namespace type
} // namespace grb
