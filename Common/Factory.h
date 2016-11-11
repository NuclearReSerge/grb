#pragma once

#include "Common/Exception.h"
#include "Common/Mapper.h"

namespace grb
{
namespace factory
{

template <typename T, typename U>
class Factory
{
public:
  Factory() = delete;
  Factory(const mapper::Mapper<U>& map)
    : _mapper(map)
  {  }
  virtual ~Factory() = default;

  virtual T* createType(const U& type) = 0;
  T* createName(const std::string& name)
  {
    U type;
    try
    {
      type = _mapper.getValue(name);
    }
    catch (Exception& )
    {
      return nullptr;
    }
    return createType(type);
  }

private:
  const mapper::Mapper<U>& _mapper;
};

} // namespace factory
} // namespace grb

#define FACTORY_CLASS_H(_factoryClass_, _typeName_, _baseClass_, _mapperSingleton_)\
namespace grb\
{\
namespace factory\
{\
class _factoryClass_ : public Factory<_baseClass_, _typeName_>\
{\
public:\
  _factoryClass_()\
    : Factory(*_mapperSingleton_::instance())\
  {\
  }\
  _baseClass_* createType(const _typeName_& type);\
};\
}\
typedef Singleton<factory::_factoryClass_> _factoryClass_;\
}

