#pragma once

#include "CLI/CommandLine.h"
#include "CLI/CommandMapper.h"
#include "CLI/CommandType.h"
#include "Common/Exception.h"

#include <list>
#include <sstream>
#include <string>

namespace grb
{

class CmdBase
{
public:
  CmdBase(type::CommandType cmdType = type::UNDEFINED_COMMAND)
    : _cmdType(cmdType), _cli(nullptr), _wasExecuted(false)
  {
  }

  virtual ~CmdBase() = default;

  type::CommandType getType() const
  {
    return _cmdType;
  }

  bool wasExecuted() const
  {
    return _wasExecuted;
  }

  CommandLine* getCLI()
  {
    return _cli;
  }
  void setCLI(CommandLine* cli)
  {
    _cli = cli;
  }

  virtual bool parse(std::list<std::string>& tokens) = 0;
  virtual void execute() = 0;
  virtual std::string help(type::CommandHelpType type = type::HELP_SHORT) = 0;

protected:
  type::CommandType _cmdType;
  CommandLine* _cli;
  bool _wasExecuted;
};


template<typename T, typename C>
class Cmd : public CmdBase
{
public:
  Cmd(type::CommandType cmdType = type::UNDEFINED_COMMAND)
    : CmdBase(cmdType)
  {
  }

  T getObjType() const
  {
    return _objType;
  }

  C getSubCommand() const
  {
    return _subCmdType;
  }

  bool
  parse(std::list<std::string>& tokens)
  {
    if (tokens.empty())
    {
      Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                    help(type::HELP_LONG), PRETTY_FUNCTION);
      throw exc;
    }

    try
    {
      _subCmdType = getMappedSubCmdVal(tokens.front());
      tokens.pop_front();
    }
    catch(Exception& )
    {
      std::stringstream ss;
      errorHeader(ss);
      ss << "Received unknown subcommand \'" << tokens.front() << "\'";
      Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                    ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    switch (static_cast<type::CmdSubCmdType>(_subCmdType))
    {
      case type::CMD_SUBCMD_CREATE:
      {
        return parseCreate(tokens);
      }
      case type::CMD_SUBCMD_HELP:
      {
        return parseHelp(tokens);
      }
      default:
      {
        if (!doParse(tokens))
          return false;
      }
    }

    if (!tokens.empty())
    {
      std::stringstream ss;
      errorHeader(ss);
      ss << "Has " << tokens.size() << " unparsed argument(s) { ";
      for (std::string arg : tokens)
      {
        ss << arg << " ";
      }
      ss << "}";
      Exception exc((type::ExceptionLevel) (type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX),
                    ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    return true;
  }

  void execute()
  {
    switch (static_cast<type::CmdSubCmdType>(_subCmdType))
    {
      case type::CMD_SUBCMD_CREATE:
      {
        executeCreate();
        break;
      }
      case type::CMD_SUBCMD_HELP:
      {
        executeHelp();
        break;
      }
      default:
      {
        doExecute();
        break;
      }
    }

    if (getCLI())
      getCLI()->incCmdIdx();
    _wasExecuted = true;
  }

  std::string help(type::CommandHelpType type)
  {
    std::string cmdName = CommandMapper::instance()->getKey(_cmdType);
    std::stringstream ss;

    if (type == type::HELP_SHORT || type == type::HELP_FULL)
    {
      if (type == type::HELP_SHORT)
      {
        ss.width(CommandHelper::maxCommandLength() + 1);
      }
      else
      {
        ss << " ";
      }
      ss << cmdName << " - " << doHelp(type::HELP_SHORT) << std::endl;
    }

    if (type == type::HELP_LONG || type == type::HELP_FULL)
    {
      ss << std::endl
         << "Usage: " << std::endl
         << "  " << (getCLI() ? getCLI()->getPrompt(false) : "") << cmdName
         << " " << doHelp(type::HELP_LONG) << std::endl;
    }
    return ss.str();
  }

protected:
  virtual T getMappedObjectVal(std::string& objStr) = 0;
  virtual C getMappedSubCmdVal(std::string& cmdStr) = 0;
  virtual std::string getMappedSubCmdStr(C cmdVal) = 0;
  virtual bool isObjectCreated() = 0;
  virtual std::string getCreatedObjectName() = 0;
  virtual bool doParse(std::list<std::string>& tokens) = 0;
  virtual void doExecute() = 0;
  virtual std::string doHelp(const type::CommandHelpType type) = 0;
  virtual void executeCreate() = 0;
  virtual void executeHelp() = 0;

  bool parseCreate(std::list<std::string>& tokens)
  {
    if (isObjectCreated())
    {
      std::stringstream ss;
      errorHeader(ss);
      ss << "Previous " << CommandMapper::instance()->getKey(_cmdType)
         << " \'" << getCreatedObjectName()
         << "\' already exists.";
      Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                    ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    if (tokens.empty())
    {
      std::stringstream ss;
      errorHeader(ss);
      ss << "Arguments required.";
      Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                    ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    try
    {
      _objType = getMappedObjectVal(tokens.front());
      tokens.pop_front();
    }
    catch (Exception& )
    {
      std::stringstream ss;
      errorHeader(ss);
      ss << "Unknown " << CommandMapper::instance()->getKey(_cmdType)
         << " \'"<< tokens.front() << "\'";
      Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                    ss.str(), PRETTY_FUNCTION);
    }

    return true;
  }

  bool parseHelp(std::list<std::string>& tokens)
  {
    if (tokens.empty())
    {
      if (isObjectCreated())
        return true;

      std::stringstream ss;
      errorHeader(ss);
      ss << "Arguments required.";
      Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                    ss.str(), PRETTY_FUNCTION);
      throw exc;
    }

    try
    {
      _objType = getMappedObjectVal(tokens.front());
      tokens.clear();
    }
    catch (Exception& )
    {
      std::stringstream ss;
      errorHeader(ss);
      ss << "Unknown " << CommandMapper::instance()->getKey(_cmdType)
         << " \'"<< tokens.front() << "\'";
      Exception exc(type::EXCEPTION_WARNING + type::EXCEPTION_MOD_NO_PREFIX,
                    ss.str(), PRETTY_FUNCTION);
    }
    return true;
  }

  void errorHeader(std::stringstream& ss)
  {
    ss << "Command \'" << CommandMapper::instance()->getKey(getType())
       << "\', subcommand \'" << getMappedSubCmdStr(_subCmdType)
       << "\' failed. ";
  }

private:
  T _objType;
  C _subCmdType;
};

} // namespace grb
