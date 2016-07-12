#include "CLI/CommandLine.h"

#include "CLI/CmdFactory.h"

#include <sstream>

namespace grb
{

namespace
{

const char* CMD_PROMPT = "GRB";
const char* WHITESPACE   = " \t\n\r\f\v";
const char DELIMITER = ' ';

}

CommandLine::CommandLine(int argc, char** argv)
  : _quit(false), _cmdIndex(0)
{
  _args.resize(argc);
  for (std::size_t i = 0; i < _args.size(); ++i)
  {
    _args[i] = argv[i];
  }
}

CommandLine::~CommandLine()
{
  _args.clear();
  for (Cmd* cmd : _commands)
  {
    delete cmd;
  }
  _commands.clear();
}

std::string
CommandLine::getBinaryName() const
{
  if (_args.empty())
    return "";

  return _args[0];
}

std::string
CommandLine::getPrompt(bool counter) const
{
  std::stringstream ss;

  ss << CMD_PROMPT;
  if (counter)
    ss << '[' << _cmdIndex << "]";
  ss << "> ";

  return ss.str();
}

Cmd*
CommandLine::parse(std::list<std::string>& tokens) throw(Exception)
{
  if (tokens.empty())
    return nullptr;

  Cmd* cmdObj = CmdFactory::instance()->create(*this, tokens.front());

  if (!cmdObj)
    return nullptr;

  tokens.pop_front();
  _commands.push_back(cmdObj);

  if (!cmdObj->parse(tokens))
    return nullptr;

  return cmdObj;
}

bool
CommandLine::quit()
{
  return _quit;
}

void
CommandLine::tokenize(const std::string& input, std::list<std::string>& tokens)
{
  std::stringstream ss(input);
  for (std::string element; std::getline(ss, element, DELIMITER);)
  {
    element.erase(0, element.find_first_not_of(WHITESPACE));
    element.erase(element.find_last_not_of(WHITESPACE) + 1);
    tokens.push_back(element);
  }
}

void
CommandLine::setQuit()
{
  _quit = true;
}

void
CommandLine::incCmdIdx()
{
  ++_cmdIndex;
}

}
