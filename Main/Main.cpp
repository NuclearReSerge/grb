#include "Analyzer/Analyzer.h"
#include "CLI/CommandLine.h"
#include "CLI/Cmd.h"
#include "Main/AnalysisData.h"

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

}

extern void intro();
extern void usage(const std::string& binaryName);

std::unique_ptr<Analyzer>&
G_Analyzer()
{
  static std::unique_ptr<Analyzer> _analyzer;
  return _analyzer;
}

std::unique_ptr<Correlation>&
G_Correlation()
{
  static std::unique_ptr<Correlation> _correlation;
  return _correlation;
}

std::unique_ptr<Catalog>&
G_CatalogData()
{
  static std::unique_ptr<Catalog> _catalog;
  return _catalog;
}

std::unique_ptr<Catalog>&
G_CatalogModel()
{
  static std::unique_ptr<Catalog> _catalog;
  return _catalog;
}

std::unique_ptr<Filter>& G_Filter()
{
  static std::unique_ptr<Filter> _filter;
  return _filter;
}

std::unique_ptr<Model>&
G_Model()
{
  static std::unique_ptr<Model> _model;
  return _model;
}

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
