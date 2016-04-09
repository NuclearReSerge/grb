#include "test/NameMapperCommon.h"

namespace grb
{
namespace test
{

const std::string NameMapperCommon::_empty;
const std::string NameMapperCommon::_invalid = "INVALID_NAME";

bool
NameMapperCommon::tryToGetIndex(const std::string& name)
{
  try
  {
    _mapper->getIndex(name);
  }
  catch (Exception& exc)
  {
    std::cout << exc.what() << std::endl;
    return false;
  }
  return true;
}

bool
NameMapperCommon::tryToGetName(const type::Index index)
{
  try
  {
    _mapper->getName(index);
  }
  catch (Exception& exc)
  {
    std::cout << exc.what() << std::endl;
    return false;
  }
  return true;
}

}
}
