#pragma once

#include "Model/Model.h"

#include <gmock/gmock.h>

namespace grb
{

class ModelMock : public Model
{
public:
  ModelMock(const type::ModelType type)
    : Model(type)
  {
  }

  MOCK_METHOD2(doParse, bool(type::ModelCmdType cmd, std::list<std::string>& tokens));
  MOCK_METHOD1(doExecute, void(type::ModelCmdType cmd));
  MOCK_METHOD1(doGenerate, void(Catalog& catalog));
  MOCK_METHOD0(doHelp, std::string());
};

} // namespace grb
