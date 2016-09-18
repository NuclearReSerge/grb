#include "test/Mock/NameMapperMock.h"
#include <gtest/gtest.h>

namespace testing
{

class NameMapperTest : public Test
{
public:
  bool tryToGetIndex(const std::string& name)
  {
    try
    {
      _mapper->getIndex(name);
    }
    catch (grb::Exception& exc)
    {
      std::cout << exc.what() << std::endl;
      return false;
    }
    return true;
  }

  bool tryToGetName(const grb::type::Index index)
  {
    try
    {
      _mapper->getName(index);
    }
    catch (grb::Exception& exc)
    {
      std::cout << exc.what() << std::endl;
      return false;
    }
    return true;
  }

protected:
  grb::mapper::NameMapper* _mapper;

  grb::type::ColumnType _columnType;
  grb::type::Index _firstIdx;
  grb::type::Index _lastIdx;
  std::string _first;
  std::string _last;

  const std::string _empty;
  const std::string _invalid = "INVALID_NAME";
};

TEST_F(NameMapperTest, isPresent_Positive)
{
  ASSERT_EQ(true, _mapper->isPresent(_first));
  ASSERT_EQ(true, _mapper->isPresent(_last));
}

TEST_F(NameMapperTest, isPresent_Negative)
{
  ASSERT_EQ(false, _mapper->isPresent(_empty));
  ASSERT_EQ(false, _mapper->isPresent(_invalid));
}

TEST_F(NameMapperTest, getIndex_Positive)
{
  ASSERT_EQ(_firstIdx, _mapper->getIndex(_first));
  ASSERT_EQ(_lastIdx, _mapper->getIndex(_last));
}

TEST_F(NameMapperTest, getIndex_Negative)
{
  ASSERT_EQ(false, tryToGetIndex(_empty));
  ASSERT_EQ(false, tryToGetIndex(_invalid));
}

TEST_F(NameMapperTest, getName_Positive)
{
  ASSERT_STREQ(_first.c_str(), _mapper->getName(_firstIdx).c_str());
  ASSERT_STREQ(_last.c_str(), _mapper->getName(_lastIdx).c_str());
}

TEST_F(NameMapperTest, getName_Negative)
{
  ASSERT_EQ(false, tryToGetName(_firstIdx - 1));
  ASSERT_EQ(false, tryToGetName(_lastIdx + 1));
}

TEST_F(NameMapperTest, getColumnType)
{
  ASSERT_EQ(_columnType, _mapper->getColumnType());
}

TEST_F(NameMapperTest, getDescription)
{
  ASSERT_EQ(false, _mapper->getDescription().empty());
}

} // namespace test
