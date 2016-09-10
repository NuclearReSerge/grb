#include "Common/Factory.h"
#include "Filter/Filter.h"
#include "Filter/FilterMapper.h"

#pragma once

FACTORY_CLASS_H(FilterFactory, type::FilterType, Filter, FilterMapper)
