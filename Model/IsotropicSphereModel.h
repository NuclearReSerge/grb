#include "Data/CatalogType.h"

#include "Model/Model.h"

#pragma once

namespace grb
{

class CatalogEntryGrbcat;

class IsotropicSphereModel : public Model
{
public:
  IsotropicSphereModel(type::ModelType type = type::ISOTROPIC_SPHERE);
  ~IsotropicSphereModel();

  std::uniform_real_distribution<>::param_type getTimeRange() const
  {
    return _time.param();
  }
  std::uniform_real_distribution<>::param_type getPhiRange() const
  {
    return _phi.param();
  }
  std::uniform_real_distribution<>::param_type getThetaRange() const
  {
    return _theta.param();
  }

protected:
  bool doParse(type::ModelCmdType cmd, std::list<std::string>& tokens) override;
  void doExecute(type::ModelCmdType cmd) override;
  void doGenerate(Catalog& catalog) override;
  std::string doHelp() override;

  void setTimeRange(double min, double max);
  void setPhiRange(double min, double max);
  void setThetaRange(double min, double max);

  CatalogEntryGrbcat* createEntry();

  type::CatalogType _catType = type::UNDEFINED_CATALOG;
  std::uniform_real_distribution<> _time;
  std::uniform_real_distribution<> _phi;
  std::uniform_real_distribution<> _theta;
  double _minValue = 0.0;
  double _maxValue = 0.0;
};

}
