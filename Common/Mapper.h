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
namespace type
{

/* *************************************************************************************************
 *
 * Pre and post incremental operators for enums defined inside type nemespace.
 *
 * ************************************************************************************************/
template <typename T>
T& operator++(T& arg)
{
  return arg = static_cast<T>( static_cast<int>(arg) + 1 );
}

template <typename T>
T operator++(T& arg, int)
{
  T temp(arg);
  arg = static_cast<T>( static_cast<int>(arg) + 1 );
  return temp;
}

} // namespace type

/* *************************************************************************************************
 *
 * Mapper class can map any class T to std::string.
 * The only requirement is that the class T has the following public operators:
 * - comparison --
 * - pre and post incremental ++
 * - out stream <<
 *
 * Eg:
 *   class T
 *   {
 *   public:
 *     bool operator==(const T&) const;
 *     T& operator++();
 *     T operator++(int);
 *     friend std::ostream& operator<<(std::ostream&, const T&);
 *   };
 *
 * ************************************************************************************************/

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
      Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
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
      Exception exc(type::EXCEPTION_WARNING, ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    return iter->first;
  }

protected:
  virtual const std::vector<std::string>& getList() const = 0;

  void initiate()
  {
    T idx = T();
    for (const std::string& name : getList())
    {
      _map.insert({name, idx++});
    }
  }

private:
  std::map<std::string, T> _map;
};

} // namespace mapper
} // namespace grb

/* *************************************************************************************************
 *
 * Macro for fast Singleton with Mapper class creation.
 * User just needs to define the getList() method.
 *
 * ************************************************************************************************/
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
