#include <memory>

#pragma once

namespace grb
{

template <typename T>
class Singleton
{
public:
  virtual ~Singleton()
  {
  }

  static T* instance()
  {
    if (!_instance.get())
      _instance.reset(new T());
    return _instance.get();
  }

protected:
  Singleton()
  {
  }

  static std::unique_ptr<T> _instance;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::_instance;

}
