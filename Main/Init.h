#include <string>

#pragma once

namespace grb
{

class Init
{
public:
  Init() = delete;

  static void intro();
  static void usage(const std::string& binaryName);

};

} // namespace grb
