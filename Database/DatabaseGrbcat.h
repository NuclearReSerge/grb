#pragma once

#include "Catalog/Coordinates.h"
#include "Database/Database.h"

namespace grb
{

class DatabaseGrbcat : public Database
{
public:
  DatabaseGrbcat()
    : Database(type::HEASARC_GRBCAT), _coordSys(type::EQUATORIAL_J2000)
  {
  }

  type::CoordinateSystemType getCoordinateSystem() const
  {
    return _coordSys;
  }

  void initialize() override;

protected:
  bool doParse(type::DatabaseCmdType cmd, std::list<std::string>& tokens) override;
  void doExecute(type::DatabaseCmdType cmd) override;
  std::string doHelp() override;

private:
  type::CoordinateSystemType _coordSys;
};

} // namespace grb
