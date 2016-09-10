#include "Common/Exception.h"
#include "Common/Singleton.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#pragma once

namespace grb
{
namespace mapper
{

template<typename T>
class Mapper
{
public:
  Mapper() = default;
  virtual ~Mapper()
  {
    _map.clear();
  }

  bool isPresent(const std::string& key) const
  {
    return _map.find(key) != _map.end();
  }

  const T& getValue(const std::string& key) const throw(Exception)
  {
    try
    {
      return _map.at(key);
    }
    catch (std::exception& stdExc)
    {
      std::stringstream ss;
      ss << "Mapper::getValue for key=" << key << " not found.";
      ss << std::endl << "std::exception.what()=" << stdExc.what() << ".";
      Exception exc(type::EXCEPTION_WARNING, ss.str().c_str(), PRETTY_FUNCTION);
      throw exc;
    }
  }

  const std::string& getKey(const T& value) const throw(Exception)
  {
    const auto iter = std::find_if(_map.begin(),
                                   _map.end(),
                                   [value](const std::pair<std::string, T>& item)
                                   { return item.second == value; });
    if (iter == _map.end())
    {
      std::stringstream ss;
      ss << "Mapper::getKey for value=" << value << " not found.";
      Exception exc(type::EXCEPTION_WARNING, ss.str().c_str(), PRETTY_FUNCTION);
      throw exc;
    }

    return iter->first;
  }

protected:
  virtual const std::vector<std::string>& getList() const = 0;

  void initiate()
  {
    std::size_t i = 0;
    for (const std::string& name : getList())
    {
      _map.insert({name, (T) i++});
    }
  }

private:
  std::map<std::string, T> _map;
};

} // namespace mapper
} // namespace grb


#define MAPPER_CLASS_H(_mapperClass_, _typeMapped_)\
namespace grb\
{\
namespace mapper\
{\
class _mapperClass_ : public Mapper<_typeMapped_>\
{\
public:\
  _mapperClass_()\
  {\
    initiate();\
  }\
protected:\
  const std::vector<std::string>& getList() const;\
};\
}\
typedef Singleton<mapper::_mapperClass_> _mapperClass_;\
}
