#include "test/Mock/CatalogEntryMock.h"
#include "test/Mock/NameMapperMock.h"

#include <gmock/gmock.h>

#pragma once

namespace grb
{

class CatalogEntryMockSample : public CatalogEntryMock
{
public:
  CatalogEntryMockSample(type::CatalogType = type::UNDEFINED_CATALOG: CatalogEntryMock(type),
      _flag(false),
      _integer(0),
      _index(-1),
      _integerRange({0, 100}),
      _indexList({0, 1, 2, 3}),
      _float(0.0),
      _string("string"),
      _stringList({"string1", "string2"}),
      _integerUnitType(type::UNDEFINED_UNIT),
      _floatUnitType(type::UNDEFINED_UNIT)
  {
    _mapper = new mapper::NameMapperMock;
  }

  ~CatalogEntryMock()
  {
    delete _mapper;
  }

  type::Flag& getFlag()
  {
    return _flag;
  }

  type::Integer& getInteger()
  {
    return _integer;
  }

  type::Index& getIndex()
  {
    return _index;
  }

  type::IntegerRange& getIntegerRange()
  {
    return _integerRange;
  }

  type::IndexList& getIndexList()
  {
    return _indexList;
  }

  type::Float& getFloat()
  {
    return _float;
  }

  type::String& getString()
  {
    return _string;
  }

  type::StringList& getStringList()
  {
    return _stringList;
  }

private:
  type::Flag _flag;
  type::Integer _integer;
  type::Index _index;
  type::IntegerRange _integerRange;
  type::IndexList _indexList;
  type::Float _float;
  type::String _string;
  type::StringList _stringList;

  type::UnitType _integerUnitType;
  type::UnitType _floatUnitType;

  mapper::NameMapper* _mapper;
};

} // namespace grb
