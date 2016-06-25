#include "Analyzer/Analyzer.h"
#include "Analyzer/Correlation.h"
#include "Data/Catalog.h"
#include "Model/ModelBase.h"

#include <memory>

#pragma once

namespace grb
{

std::unique_ptr<Catalog>& G_CatalogData();
std::unique_ptr<Catalog>& G_CatalogModel();
std::unique_ptr<ModelBase>& G_Model();
std::unique_ptr<Analyzer>& G_Analyzer();
std::unique_ptr<Correlation>& G_Correlation();

}
