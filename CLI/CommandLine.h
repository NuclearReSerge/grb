#include "Common/Exception.h"

#include <list>
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
  std::string getPrompt(bool counter = true) const;

  Cmd* parse(std::list<std::string>& tokens) throw(Exception);
  bool quit()
  {
    return _quit;
  }

  static void tokenize(const std::string& input, std::list<std::string>& tokens,
                       const char delim = ' ');
protected:
  friend class Cmd;
  friend class CmdQuit;

  void incCmdIdx()
  {
    ++_cmdIndex;
  }

  void setQuit()
  {
    _quit = true;
  }

private:
  bool _quit;
  std::size_t _cmdIndex;
  std::vector<std::string> _args;
  std::list<Cmd*> _commands;
};

} // namespace grb
