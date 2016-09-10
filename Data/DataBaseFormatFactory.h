#include "Common/Factory.h"
#include "Data/DataBaseFormat.h"
#include "Data/DataBaseFormatMapper.h"

#pragma once

FACTORY_CLASS_H(DataBaseFormatFactory, type::DatabaseFormatType, DataBaseFormat, DataBaseFormatMapper)
