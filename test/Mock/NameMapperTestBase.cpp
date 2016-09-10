#include "test/Mock/NameMapperTestBase.h"

namespace testing
{

const std::string NameMapperTestBase::_empty;
const std::string NameMapperTestBase::_invalid = "INVALID_NAME";

bool
NameMapperTestBase::tryToGetIndex(const std::string& name)
{
  try
  {
    _mapper->getIndex(name);
  }
  catch (grb::Exception& exc)
  {
    std::cout << exc.what() << std::endl;
    return false;
  }
  return true;
}

bool
NameMapperTestBase::tryToGetName(const grb::type::Index index)
{
  try
  {
    _mapper->getName(index);
  }
  catch (grb::Exception& exc)
  {
    std::cout << exc.what() << std::endl;
    return false;
  }
  return true;
}

} // namespace testing
