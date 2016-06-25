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

extern void intro();
extern void usage(const std::string& binaryName);

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

std::unique_ptr<ModelBase>&
G_Model()
{
  static std::unique_ptr<ModelBase> _model;
  return _model;
}

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
    std::cin.getline(buff, buffSize);
    std::cin.clear();
    std::string cmdLine(buff);

    try
    {
      grb::Cmd* cmdObj = cli.parse(cmdLine);
      if(cmdObj)
      {
        cmdObj->execute();
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
