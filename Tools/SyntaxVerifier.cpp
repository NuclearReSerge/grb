#include "SyntaxVerifier.h"

#include <bitset>
#include <iterator>

namespace
{
  const char* leftBraket = "(";
  const char* rightBraket = ")";
  const char* comma = ",";

  const std::vector<std::string> rangeFormat { leftBraket, "<min>" , comma, "<max>", rightBraket };
}

namespace grb
{

bool
SyntaxVerifier::verifyRange()
{
  if (std::distance(_begin, _end) != 5)
    return false;

  std::bitset<5> tokenTest;
  std::size_t i = 0;
  auto iter = _begin;

  while (iter != _end)
  {
    switch (i)
    {
      case 0:
      case 2:
      case 4:
      {
        if (*iter == rangeFormat[i])
          tokenTest.set(i);
        break;
      }
      case 1:
      case 3:
      {
        if (!iter->empty())
        {
          _extracted.push_back(&(*iter));
          tokenTest.set(i);
        }
        break;
      }
    }

    ++i;
    iter++;
  }

  if (tokenTest.all())
    return true;

  _extracted.clear();
  return false;
}

} // nmaespace grb
