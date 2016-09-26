#include "test/Mock/FactoryMock.h"

#include <gtest/gtest.h>

namespace
{

std::vector<std::string> LIST =
{
  "BASE",
  "TYPE1",
  "TYPE2",

  // LAST
  "undefined type"
};

enum Type
{
  BASE = 0,
  TYPE_1,
  TYPE_2,

  // LAST
  UNDEFINED_TYPE
};

Type operator++(Type& arg, int)
{
  Type temp(arg);
  arg = static_cast<Type>( static_cast<int>(arg) + 1 );
  return temp;
}

class Base
{
public:
  Base(const Type id = UNDEFINED_TYPE)
    :_id(id)
  {
  }
  virtual ~Base() = default;
  Type type() const
  {
    return _id;
  }
  virtual std::string name() const = 0;
private:
  Type _id;
};

class Type1 : public Base
{
public:
  Type1() : Base(TYPE_1) { }
  std::string name() const { return LIST[type()]; }
};

class Type2 : public Base
{
public:
  Type2() : Base(TYPE_2) { }
  std::string name() const { return LIST[type()]; }
};

} // namespace

namespace testing
{

class FactoryTest : public Test
{
public:
  Base* createTypeTest(const Type& type)
  {
    switch (type)
    {
      case TYPE_1:
        return new Type1;
      case TYPE_2:
        return new Type2;
      default:
        break;
    }
    return nullptr;
  }

protected:
  void SetUp()
  {
    _mapper = new grb::mapper::MapperMock<Type>();
    _factory = new grb::factory::FactoryMock<Base, Type>(*_mapper);

    EXPECT_CALL(*_mapper, getList())
        .Times(1)
        .WillOnce(ReturnRef(LIST));

    EXPECT_CALL(*_factory, createType(_))
        .WillRepeatedly(Invoke(this, &FactoryTest::createTypeTest));

    _mapper->initiateMock();
  }

  void TearDown()
  {
    delete _factory;
    delete _mapper;
    delete _base;
  }

  grb::mapper::MapperMock<Type>* _mapper;
  grb::factory::FactoryMock<Base, Type>* _factory;
  Base* _base { nullptr };
  std::string _name;
  Type _type;
};

TEST_F(FactoryTest, createName_Unknown)
{
  _name = "name";

  ASSERT_NO_THROW(_base = _factory->createName(_name));

  ASSERT_EQ((Base*) nullptr, _base);
}

TEST_F(FactoryTest, createName_Type1_Positive)
{
  _type = TYPE_1;
  _name = LIST[_type];

  ASSERT_NO_THROW(_base = _factory->createName(_name));

  ASSERT_NE((Base*) nullptr, _base);
  ASSERT_EQ(_type, _base->type());
  ASSERT_STREQ(_name.c_str(), _base->name().c_str());
}

TEST_F(FactoryTest, createName_Type2_Positive)
{
  _type = TYPE_2;
  _name = LIST[_type];

  ASSERT_NO_THROW(_base = _factory->createName(_name));

  ASSERT_NE((Base*) nullptr, _base);
  ASSERT_EQ(_type, _base->type());
  ASSERT_STREQ(_name.c_str(), _base->name().c_str());
}

TEST_F(FactoryTest, createName_Base_Negative)
{
  _type = BASE;
  _name = LIST[_type];

  ASSERT_NO_THROW(_base = _factory->createName(_name));

  ASSERT_EQ((Base*) nullptr, _base);
}

TEST_F(FactoryTest, createType_Type1_Positive)
{
  _type = TYPE_1;
  _name = LIST[_type];

  ASSERT_NO_THROW(_base = _factory->createType(_type));

  ASSERT_NE((Base*) nullptr, _base);
  ASSERT_EQ(_type, _base->type());
  ASSERT_STREQ(_name.c_str(), _base->name().c_str());
}

TEST_F(FactoryTest, createType_Type2_Positive)
{
  _type = TYPE_2;
  _name = LIST[_type];

  ASSERT_NO_THROW(_base = _factory->createType(_type));

  ASSERT_NE((Base*) nullptr, _base);
  ASSERT_EQ(_type, _base->type());
  ASSERT_STREQ(_name.c_str(), _base->name().c_str());
}

TEST_F(FactoryTest, createType_Base_Negative)
{
  _type = BASE;

  ASSERT_NO_THROW(_base = _factory->createType(_type));

  ASSERT_EQ((Base*) nullptr, _base);
}

} // namespace testing
