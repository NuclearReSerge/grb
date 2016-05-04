#include "Common/Exception.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#pragma once

namespace grb
{

template<typename T>
class Mapper
{
public:
  Mapper();
  virtual ~Mapper();

  bool isPresent(const std::string& key) const;
  T getValue(const std::string& key) const throw(Exception);
  const std::string& getKey(const T& value) const throw(Exception);

protected:
  virtual const std::vector<std::string>& getList() const = 0;
  void initiate();

  std::map<std::string, T> _map;

};

template<typename T>
Mapper<T>::Mapper()
{
}

template<typename T>
Mapper<T>::~Mapper()
{
  _map.clear();
}

template<typename T>
bool
Mapper<T>::isPresent(const std::string& key) const
{
  return _map.find(key) != _map.end();
}

template<typename T>
T
Mapper<T>::getValue(const std::string& key) const throw(Exception)
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

template<typename T>
const std::string&
Mapper<T>::getKey(const T& value) const throw(Exception)
{
  const auto iter = std::find_if(_map.begin(), _map.end(),
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

template<typename T>
void
Mapper<T>::initiate()
{
  std::size_t i = 0;
  for (const std::string& name : getList())
  {
    _map.insert({name, (T) i++});
  }
}

}
