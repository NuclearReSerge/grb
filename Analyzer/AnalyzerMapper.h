#include "Common/Singleton.h"
#include "Tools/Mapper.h"

#pragma once

namespace grb
{

namespace type
{

enum AnalyzerType
{
  GRBCAT_ANALYZER,

  // LAST
  UNDEFINED_ANALYZER
};

}

namespace mapper
{

class AnalyzerMapper : public Mapper<type::AnalyzerType>
{
public:
  AnalyzerMapper();

protected:
  const std::vector<std::string>& getList() const;
};

}

typedef Singleton<mapper::AnalyzerMapper> AnalyzerMapper;

}
