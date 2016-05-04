#include "Common/Exception.h"
#include "Common/Global.h"

#include <list>
#include <map>
#include <string>
#include <vector>

#pragma once

namespace grb
{

class Cmd;

class CommandLine
{
public:
  CommandLine() = delete;
  CommandLine(int argc, char** argv);
  ~CommandLine();

  std::string getBinaryName() const;
  std::string getPrompt() const;

  Cmd* parse(const std::string& input) throw(Exception);
  bool quit();

protected:
  friend class Cmd;
  friend class CmdQuit;
  void incCmdIdx();
  void setQuit();

  void tokenize(const std::string& input, std::list<std::string>& words);
private:
  bool _quit;
  std::size_t _cmdIndex;
  std::vector<std::string> _args;
  std::list<Cmd*> _commands;
};

}
