#include "Model/Model.h"

#pragma once

namespace grb
{

class IsotropicBallModel : public Model
{
public:
  IsotropicBallModel();
  ~IsotropicBallModel();

  bool parse(std::list<std::string>& tokens);
  void generate(Catalog& catalog);

protected:
  void setTimeRange(double min, double max);
  void setRadiusRange(double min, double max);
  void setPhiRange(double min, double max);
  void setThetaRange(double min, double max);

private:
  std::uniform_real_distribution<> _time;
  std::uniform_real_distribution<> _r;
  std::uniform_real_distribution<> _phi;
  std::uniform_real_distribution<> _theta;
};

}
