#include "Analyzer/Analyzer.h"
#include "Correlation/Correlation.h"
#include "Data/Catalog.h"
#include "Filter/Filter.h"
#include "Model/Model.h"

#include <memory>

#pragma once

namespace grb
{

std::unique_ptr<Analyzer>& G_Analyzer();
std::unique_ptr<Correlation>& G_Correlation();
std::unique_ptr<Catalog>& G_CatalogData();
std::unique_ptr<Catalog>& G_CatalogModel();
std::unique_ptr<Filter>& G_Filter();
std::unique_ptr<Model>& G_Model();


}
