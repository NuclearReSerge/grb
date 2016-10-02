#include "test/Mock/MockHelper.h"

#include <iostream>

namespace testing
{

#ifdef TEST_PRINT_EXC
void printWhat(grb::Exception& exc)
{
  std::cout << exc.what() << std::endl;
}
#else
void printWhat(grb::Exception&)
{
}
#endif

} // namespace testing
