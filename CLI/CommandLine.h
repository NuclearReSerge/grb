#include "Common/Exception.h"

#include <list>
#include <string>
#include <vector>

#pragma once

namespace grb
{

class Cmd;

extern const std::string CMD_PROMPT;

class CommandLine
{
public:
  CommandLine() = delete;
  CommandLine(int argc, char** argv);
  virtual ~CommandLine();

  std::string getBinaryName() const;
  std::string getPrompt(bool counter = true) const;
  Cmd* parse(std::list<std::string>& tokens) throw(Exception);
  static void tokenize(const std::string& input, std::list<std::string>& tokens,
                       const char delim = ' ');

  bool quit()
  {
    return _quit;
  }
  void setQuit()
  {
    _quit = true;
  }
  void incCmdIdx()
  {
    ++_cmdIndex;
  }

protected:
  virtual Cmd* createCommand(const std::string& name);

private:
  bool _quit;
  std::size_t _cmdIndex;
  std::vector<std::string> _args;
  std::list<Cmd*> _commands;
};

} // namespace grb
