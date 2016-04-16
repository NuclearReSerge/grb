#include "Data/Catalog.h"
#include "Data/DataBaseFormatFactory.h"
#include "Tools/Parser.h"

#include <iostream>
#include <memory>
#include <string>

/** ************************************************************************************************
 *
 * Init.cpp
 *
 **************************************************************************************************/

namespace grb
{
extern void intro();
extern void usage(const char* binName);
extern bool filenameMapping(const std::string& filename, type::DatabaseTableType& dbType,
                            type::CatalogType& catType);
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

  if (argc < 2)
  {
    grb::usage(argv[0]);
    return 1;
  }

  std::string filename(argv[1]);
  grb::type::DatabaseTableType dbType(grb::type::DATABASE_TABLE_TYPE_UNDEFINED);
  grb::type::CatalogType catType(grb::type::CATALOG_TYPE_UNDEFINED);
  if (!grb::filenameMapping(filename, dbType, catType))
  {
    grb::usage(argv[0]);
    return 2;
  }

  std::unique_ptr<grb::Catalog> catalog;
  catalog.reset(new grb::Catalog(catType));
  try
  {
    grb::Parser parser(filename,
                       grb::DataBaseFormatFactory::instance()->getFormat(dbType),
                       *catalog.get());
    std::size_t rows = parser.parse();
    std::cout << "Parsing successful. Extraced " << rows << " rows." << std::endl;
  }
  catch (grb::Exception& exc)
  {
    std::cout << "Parsing failed." << std::endl;
    std::cerr << exc.what() << std::endl;
    return 3;
  }

  return 0;
}
