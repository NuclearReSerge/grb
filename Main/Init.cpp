#include <cstdio>
#include <string>

namespace grb
{

namespace
{

const char* LINE_78_ASTER = "******************************************************************************";
const char* PROGRAM_NAME = "Gamma-Ray Burst Correlation Analyzer";

}

void
intro()
{
  std::printf("*%s*\n*%78s*\n* %s ver. %2.2f%s%30s*\n*%78s*\n*%s*\n\n",
              LINE_78_ASTER,
              "",
              PROGRAM_NAME, GRB_VERSION, (GRB_VERSION < 10.0 ? " " : ""), "",
              "",
              LINE_78_ASTER);
}

void
usage(const std::string& binaryName)
{
  std::printf("Usage: %s <DB_FILE_NAME>.tdat\n\n\t<DB_FILE_NAME> : name corresponding to database "
              "table name form dbms1.gsfc.nasa.gov\n\n",
              binaryName.c_str());
}

}
