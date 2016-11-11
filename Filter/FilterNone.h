#pragma once

#include "Filter/Filter.h"

namespace grb
{

class FilterNone : public Filter
{
public:
  FilterNone();
  ~FilterNone();

protected:
  bool doParse(const type::FilterCmdType cmd, std::list<std::string>& tokens) override;
  void doExecute(const type::FilterCmdType cmd) override;
  std::string doHelp() override;
  bool isCommandValid(const type::FilterCmdType cmd) override;
};

} // namespace grb
