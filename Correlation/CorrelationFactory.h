#include "Common/Factory.h"
#include "Correlation/Correlation.h"
#include "Correlation/CorrelationMapper.h"

FACTORY_CLASS_H(CorrelationFactory, type::CorrelationType, Correlation, CorrelationMapper)
