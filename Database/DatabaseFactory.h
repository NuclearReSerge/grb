#pragma once

#include "Common/Factory.h"
#include "Database/Database.h"
#include "Database/DatabaseMapper.h"

FACTORY_CLASS_H(DatabaseFactory, type::DatabaseType, Database, DatabaseMapper)
