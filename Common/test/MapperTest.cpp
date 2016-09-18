#include "test/Mock/MapperMock.h"

#include <gtest/gtest.h>

namespace
{

constexpr int DEFAULT = 100;
const std::string EMPTY = "";
const std::string INVALID = "INVALID_NAME";

std::vector<std::string> LIST =
{
  "string_0x01",
  "string_0x02",
  "string_0x03",
  "string_0x04",
  "string_0x05",
  "string_0x06",
  "string_0x07",
  "string_0x08",
  "string_0x09",
  "string_0x0A",
  "string_0x0B",
  "string_0x0C",
  "string_0x0D",
  "string_0x0E",
  "string_0x0F"
};

class TestClass
{
public:
  TestClass(int idx = DEFAULT)
    : _idx(idx)
  {
  }
  bool operator==(const TestClass& lhs) const
  {
    return lhs.get() == this->get();
  }
  TestClass& operator++()
  {
    increment();
    return *this;
  }
  TestClass operator++(int)
  {
    TestClass temp(this->get());
    this->increment();
    return temp;
  }
  friend std::ostream& operator<<(std::ostream& stream, const TestClass& obj)
  {
    stream << "TestClass(" << obj.get() << ")";
    return stream;
  }

  int get() const
  {
    return _idx;
  }
  void increment()
  {
    ++_idx;
  }

private:
  int _idx;
};

} // namespace

namespace testing
{

class MapperTest : public Test
{
protected:
  void SetUp()
  {
    EXPECT_CALL(_mapInt, getList())
        .Times(1)
        .WillOnce(ReturnRef(LIST));
    EXPECT_CALL(_mapClass, getList())
        .Times(1)
        .WillOnce(ReturnRef(LIST));

    _mapInt.initiateMock();
    _mapClass.initiateMock();
  }

  void TearDown()
  {
  }

  void printWhat(grb::Exception& /*exc*/)
  {
    //std::cout << exc.what() << std::endl;
  }

  grb::mapper::MapperMock<int> _mapInt;
  grb::mapper::MapperMock<TestClass> _mapClass;
};

TEST_F(MapperTest, isPresent_Positive)
{
  ASSERT_EQ(true, _mapInt.isPresent(LIST.front()));
  ASSERT_EQ(true, _mapInt.isPresent(LIST.back()));
  ASSERT_EQ(true, _mapClass.isPresent(LIST.front()));
  ASSERT_EQ(true, _mapClass.isPresent(LIST.back()));
}

TEST_F(MapperTest, isPresent_Negative)
{
  ASSERT_EQ(false, _mapInt.isPresent(EMPTY));
  ASSERT_EQ(false, _mapInt.isPresent(INVALID));
  ASSERT_EQ(false, _mapClass.isPresent(EMPTY));
  ASSERT_EQ(false, _mapClass.isPresent(INVALID));
}

TEST_F(MapperTest, getValue_Positive)
{
  int val = 0;

  ASSERT_NO_THROW(val = _mapInt.getValue(LIST.front()));
  ASSERT_EQ(0, val);

  ASSERT_NO_THROW(val = _mapInt.getValue(LIST.back()));
  ASSERT_EQ(LIST.size() - 1, val);

  ASSERT_NO_THROW(val = _mapClass.getValue(LIST.front()).get());
  ASSERT_EQ(DEFAULT, val);

  ASSERT_NO_THROW(val = _mapClass.getValue(LIST.back()).get());
  ASSERT_EQ(DEFAULT + LIST.size() - 1, val);
}

TEST_F(MapperTest, getValue_Negative)
{
  ASSERT_THROW(_mapInt.getValue(EMPTY), grb::Exception);
  ASSERT_THROW(_mapInt.getValue(INVALID), grb::Exception);
  ASSERT_THROW(_mapClass.getValue(EMPTY), grb::Exception);
  ASSERT_THROW(_mapClass.getValue(INVALID), grb::Exception);
}

TEST_F(MapperTest, getValue_Negative_what)
{
  try
  {
    _mapInt.getValue(INVALID);
  }
  catch (grb::Exception& exc)
  {
    printWhat(exc);
  }

  try
  {
    _mapClass.getValue(INVALID);
  }
  catch (grb::Exception& exc)
  {
    printWhat(exc);
  }
}

TEST_F(MapperTest, getKey_Positive)
{
  std::string key;

  ASSERT_NO_THROW(key = _mapInt.getKey(0));
  ASSERT_STREQ(LIST.front().c_str(), key.c_str());

  ASSERT_NO_THROW(key = _mapInt.getKey(LIST.size() - 1));
  ASSERT_STREQ(LIST.back().c_str(), key.c_str());

  ASSERT_NO_THROW(key = _mapClass.getKey(TestClass(DEFAULT)));
  ASSERT_STREQ(LIST.front().c_str(), key.c_str());

  ASSERT_NO_THROW(key = _mapClass.getKey(TestClass(DEFAULT + LIST.size() - 1)));
  ASSERT_STREQ(LIST.back().c_str(), key.c_str());
}

TEST_F(MapperTest, getKey_Negative)
{
  ASSERT_THROW(_mapInt.getKey(-1), grb::Exception);
  ASSERT_THROW(_mapInt.getKey(LIST.size()), grb::Exception);
  ASSERT_THROW(_mapClass.getKey(TestClass(DEFAULT - 1)), grb::Exception);
  ASSERT_THROW(_mapClass.getKey(TestClass(DEFAULT + LIST.size())), grb::Exception);
}

TEST_F(MapperTest, getKey_Negative_what)
{
  try
  {
    _mapInt.getKey(-1);
  }
  catch (grb::Exception& exc)
  {
    printWhat(exc);
  }

  try
  {
    _mapClass.getKey(TestClass(DEFAULT - 1));
  }
  catch (grb::Exception& exc)
  {
    printWhat(exc);
  }
}

} // namespace testing
