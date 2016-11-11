#pragma once

#include "Common/Factory.h"
#include "Model/Model.h"
#include "Model/ModelMapper.h"

FACTORY_CLASS_H(ModelFactory, type::ModelType, Model, ModelMapper)
