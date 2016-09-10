#include "Analyzer/Analyzer.h"
#include "Analyzer/AnalyzerMapper.h"
#include "Common/Factory.h"

#pragma once

FACTORY_CLASS_H(AnalyzerFactory, type::AnalyzerType, Analyzer, AnalyzerMapper)
