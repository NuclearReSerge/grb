#include "Common/Exception.h"
#include "Common/Global.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

class NameMapper : public Mapper<type::Index>
{
public:
  NameMapper() = delete;
  NameMapper(const type::ColumnType columnType, const std::string& description);

  type::Index getIndex(const std::string& name) const throw(Exception);
  const std::string& getName(const type::Index& index) const throw(Exception);

  type::ColumnType getColumnType() const;
  const std::string& getDescription() const;

protected:
  const type::ColumnType _columnType;
  const std::string& _description;

};

}
