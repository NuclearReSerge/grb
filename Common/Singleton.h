#pragma once

#include <memory>

namespace grb
{

template <typename T>
class Singleton
{
public:
  Singleton(const Singleton& ) = delete;
  Singleton& operator=(const Singleton& ) = delete;
  virtual ~Singleton() = default;

  static T* instance()
  {
    if (!_instance.get())
      _instance.reset(new T());
    return _instance.get();
  }

protected:
  Singleton() = default;

  static std::unique_ptr<T> _instance;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::_instance;

}
