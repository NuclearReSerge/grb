#include "Tools/NameMapper.h"
#include "Common/Singleton.h"

#pragma once

namespace grb
{

class ReferenceType : public NameMapper
{
protected:
  friend class Singleton<ReferenceType>;

  ReferenceType();
  const VectorString& getNameList() const;
};

typedef Singleton<ReferenceType> Reference;
}
