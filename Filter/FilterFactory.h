#pragma once

#include "Common/Factory.h"
#include "Filter/Filter.h"
#include "Filter/FilterMapper.h"

FACTORY_CLASS_H(FilterFactory, type::FilterType, Filter, FilterMapper)
