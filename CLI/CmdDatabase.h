#include "CLI/Cmd.h"

#pragma once

namespace grb
{

class CmdDatabase : public Cmd
{
public:
  CmdDatabase(CommandLine& cli);

protected:
  bool doParse(std::list<std::string>& tokens);
  void doExecute();
  std::string doHelp(type::HelpType type);

  bool filenameMapping(const std::string& filename);



private:
  std::string _dbFile;
  std::string _dbFilename;

};

}
