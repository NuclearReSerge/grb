#include <list>
#include <string>
#include <vector>

#pragma once

namespace grb
{

class SyntaxVerifier
{
public:
  SyntaxVerifier(const std::list<std::string>& tokens)
    : _begin(tokens.cbegin()), _end(tokens.cend())
  {
  }
  SyntaxVerifier(const std::list<std::string>::const_iterator begin,
                 const std::list<std::string>::const_iterator end)
    : _begin(begin), _end(end)
  {
  }
  ~SyntaxVerifier()
  {
    _extracted.clear();
  }


  bool verifyRange();

  const std::vector<const std::string*>& getExtracted() const
  {
    return _extracted;
  }

private:
  const std::list<std::string>::const_iterator _begin;
  const std::list<std::string>::const_iterator _end;
  std::list<std::string>::const_iterator iter;

  std::vector<const std::string*> _extracted;
};

} // namespace grb
