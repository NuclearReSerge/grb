#pragma once

#include "Common/Exception.h"
#include "Common/Global.h"
#include "Common/Mapper.h"
#include "Data/ColumnType.h"

namespace grb
{
namespace mapper
{

class NameMapper : public Mapper<type::Index>
{
public:
  NameMapper(const type::ColumnType columnType = type::UNDEFINED_COLUMN)
    : _columnType(columnType)
  {
  }

  type::ColumnType getColumnType() const
  {
    return _columnType;
  }

  type::Index getIndex(const std::string& name) const throw(Exception);
  const std::string& getName(const type::Index& index) const throw(Exception);

  virtual const std::string& getDescription() const = 0;

protected:  
  const type::ColumnType _columnType;
};

} // namespace mapper
} // namespace grb

#define NAME_MAPPER_CLASS_H(_nameMapperClass_, _columnType_)\
namespace grb\
{\
namespace mapper\
{\
class _nameMapperClass_ : public NameMapper\
{\
public:\
  _nameMapperClass_()\
    : NameMapper(_columnType_)\
  {\
    initiate();\
  }\
  const std::string& getDescription() const override;\
protected:\
  const std::vector<std::string>& getList() const override;\
};\
}\
typedef Singleton<mapper::_nameMapperClass_> _nameMapperClass_;\
}
