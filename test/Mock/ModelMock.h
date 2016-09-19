#include "Model/Model.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class ModelMock : public Model
{
public:
  ModelMock()
    : Model()
  {
  }

  MOCK_METHOD2(doParse, bool(type::ModelCmdType cmd, std::list<std::string>& tokens));
  MOCK_METHOD1(doGenerate, void(Catalog& catalog));
  MOCK_METHOD0(doHelp, std::string());
};

} // namespace grb
