#pragma once

#include "Filter/Filter.h"

#include "gmock/gmock.h"

namespace grb
{

class FilterMock : public Filter
{
public:
  FilterMock(type::FilterType type)
    : Filter(type)
  {
  }

  MOCK_METHOD2(doParse, bool(type::FilterCmdType cmd, std::list<std::string>& tokens));
  MOCK_METHOD1(doExecute, void(type::FilterCmdType cmd));
  MOCK_METHOD0(doHelp, std::string());
};

} // namespace grb
