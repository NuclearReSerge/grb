#pragma once

#include <list>
#include <string>

namespace grb
{

template<typename T, typename C>
class BaseObject
{
public:
  BaseObject(const T type)
    : _type(type)
  {
  }
  virtual ~BaseObject() = default;

  T getType() const
  {
    return _type;
  }

  bool parse(const C cmd, std::list<std::string>& tokens)
  {
    if (!tokens.empty())
      return false;

    if (!isCommandValid(cmd))
      return false;

    return doParse(cmd, tokens);
  }

  void execute(const C cmd)
  {
    doExecute(cmd);
  }

  std::string help()
  {
    return doHelp();
  }

protected:
  virtual bool doParse(const C cmd, std::list<std::string>& tokens) = 0;
  virtual void doExecute(const C cmd) = 0;
  virtual std::string doHelp() = 0;
  virtual bool isCommandValid(const C cmd) = 0;

private:
  T _type;
};

} // namespace grb
