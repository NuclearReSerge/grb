#include "Common/Factory.h"
#include "Model/Model.h"
#include "Model/ModelMapper.h"

#pragma once

FACTORY_CLASS_H(ModelFactory, type::ModelType, Model, ModelMapper)
