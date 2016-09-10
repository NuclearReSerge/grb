#include "Analyzer/Analyzer.h"
#include "CLI/CommandLine.h"
#include "CLI/Cmd.h"
#include "Main/AnalysisData.h"

#include <iostream>
#include <memory>
#include <string>

namespace grb
{
namespace type
{

enum ErrorLevelCode
{
  NO_ERROR,
  COMMAND_LINE_PARSING_FAILED,
  DATABASE_PARSING_FAILED,

  // LAST
  ERROR_LEVEL_CODE_UNDEFINED
};

} // namespace type
} // namespace grb

/** ************************************************************************************************
 *
 * Main/Init.cpp
 *
 **************************************************************************************************/

namespace grb
{

extern void intro();
extern void usage(const std::string& binaryName);

} // namespace grb

/** ************************************************************************************************
 *
 * MAIN
 *
 **************************************************************************************************/
namespace
{

const std::size_t buffSize = 256;
char buff[buffSize];

} // namespace

int
main(int argc, char** argv)
{
  grb::intro();
  grb::CommandLine cli(argc, argv);

  while (!cli.quit())
  {
    std::cout << cli.getPrompt();
    std::cout.flush();

    std::cin.getline(buff, buffSize);
    std::cin.clear();

    if (!buff[0])
      continue;

    std::list<std::string> tokens;
    grb::CommandLine::tokenize(buff, tokens);

    try
    {
      grb::Cmd* cmdObj = cli.parse(tokens);
      if(cmdObj)
      {
        cmdObj->execute();
      }
      else
      {
        std::cerr << "Unknown command '" << tokens.front() << "'"<< std::endl;
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
