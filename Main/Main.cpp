#include "Analyzer/Analyzer.h"
#include "CLI/CommandLine.h"
#include "CLI/Cmd.h"

#include <iostream>
#include <memory>
#include <string>

/** ************************************************************************************************
 *
 * Main/Init.cpp
 *
 **************************************************************************************************/

namespace grb
{

extern void intro();
extern void usage(const std::string& binaryName);

}

namespace
{

const std::size_t buffSize = 256;
char buff[buffSize];

}

/** ************************************************************************************************
 *
 * MAIN
 *
 **************************************************************************************************/
int
main(int argc, char** argv)
{
  grb::intro();
  grb::CommandLine cli(argc, argv);

  grb::Analyzer* analyzer = nullptr;

  while (!cli.quit())
  {
    std::cout << cli.getPrompt();
    std::cin.getline(buff, buffSize);
    std::cin.clear();
    std::string cmdLine(buff);

    try
    {
      grb::Cmd* cmdObj = cli.parse(cmdLine);
      if(cmdObj)
      {
        cmdObj->execute(analyzer);
      }
      else
      {
        std::cerr << "Unknown command '" << cmdLine << "'"<< std::endl;
      }
    }
    catch (grb::Exception& exc)
    {
      std::cerr << exc.what() << std::endl;
      if (exc.getLevel() == grb::type::EXCEPTION_CRITICAL)
      {
        //grb::usage(cli.getBinaryName());
        return grb::type::COMMAND_LINE_PARSING_FAILED;
      }
    }
  }

  return grb::type::NO_ERROR;
}
