#include "Model/IsotropicSphereModel.h"

#pragma once

namespace grb
{

class IsotropicBallModel : public IsotropicSphereModel
{
public:
  IsotropicBallModel(type::ModelType type = type::ISOTROPIC_BALL);
  ~IsotropicBallModel();

  std::uniform_real_distribution<>::param_type getRadiusRange() const
  {
    return _r.param();
  }

protected:
  bool doParse(type::ModelCmdType cmd, std::list<std::string>& tokens) override;
  void doExecute(type::ModelCmdType cmd) override;
  std::string doHelp() override;

  void setRadiusRange(double min, double max);

  std::uniform_real_distribution<> _r;
};

}
