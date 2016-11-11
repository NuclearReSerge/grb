#include "FilterNone.h"

namespace grb
{

FilterNone::FilterNone()
  : Filter(type::FILTER_NONE)
{
}

FilterNone::~FilterNone()
{
}

bool
FilterNone::doParse(const type::FilterCmdType cmd, std::list<std::string>& tokens)
{
  switch (cmd)
  {
    default:
      break;
  }

  tokens.clear();

  return true;
}

void
FilterNone::doExecute(const type::FilterCmdType cmd)
{
  switch (cmd)
  {
    default:
      break;
  }
}

std::string
FilterNone::doHelp()
{
  return "FilterNone::doHelp";
}

bool
FilterNone::isCommandValid(const type::FilterCmdType /*cmd*/)
{
  return true;
}



} // namespace grb
