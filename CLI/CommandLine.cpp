#include "CLI/CommandLine.h"

#include "CLI/CommandFactory.h"

#include <iostream>
#include <sstream>

namespace grb
{

const std::string CMD_PROMPT = "GRB";

namespace
{

const std::string WHITESPACE   = " \t\n\r\f\v";
const std::string DELIM = " ";
const std::string SPECIAL = "=,[]()";

} // namespace

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

  Cmd* cmdObj = createCommand(tokens.front());

  if (!cmdObj)
    return nullptr;

  cmdObj->setCLI(this);
  tokens.pop_front();

  bool res = false;

  try
  {
    res = cmdObj->parse(tokens);
  }
  catch (Exception& exc)
  {
    delete cmdObj;
    throw;
  }

  if (!res)
  {
    delete cmdObj;
    return nullptr;
  }

  _commands.push_back(cmdObj);
  return cmdObj;
}

void
CommandLine::tokenize(const std::string& input, std::list<std::string>& tokens, const char delim)
{
  std::string dummy(input);

  for (size_t i = 0; i< SPECIAL.size(); ++i)
  {
    size_t pos = 0;
    while ((pos = dummy.find(SPECIAL[i], pos)) != std::string::npos)
    {
      dummy.insert(pos+1, DELIM);
      dummy.insert(pos, DELIM);
      pos += 2;
    }
  }

  std::stringstream ss(dummy);
  for (std::string element; std::getline(ss, element, delim);)
  {
    element.erase(0, element.find_first_not_of(WHITESPACE));
    element.erase(element.find_last_not_of(WHITESPACE) + 1);

    if (!element.empty())
      tokens.push_back(element);
  }
}

Cmd*
CommandLine::createCommand(const std::string& name)
{
  return CommandFactory::instance()->createName(name);
}

} // namespace grb
