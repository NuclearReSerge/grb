#include "Data/DataBaseFormatFactory.h"

#include "test/Mock/FactoryTestFixtures.h"

namespace testing
{

class DataBaseFormatFactoryTest :
    public FactoryTestFixturesBase<grb::type::DataBaseFormatType, grb::DataBaseFormat, grb::factory::DataBaseFormatFactory>
{
protected:
  void SetUp()
  {
    _invalidType = grb::type::UNDEFINED_DATABASE_FORMAT;
    _invalidName = "undefined-database-table";
  }
};

} // namespace testing

FACTORY_TEST_FIXTURES(DataBaseFormatFactoryTest)

namespace testing
{

TEST_F(DataBaseFormatFactoryTest, createName_DataBaseFormatGrbcat)
{
  _validType = grb::type::HEASARC_GRBCAT;
  _validName = "heasarc_grbcat";
  callCreateName();
}

TEST_F(DataBaseFormatFactoryTest, createType_DataBaseFormatGrbcat)
{
  _validType = grb::type::HEASARC_GRBCAT;
  callCreateType();
}

TEST_F(DataBaseFormatFactoryTest, createType_DataBaseFormatGrbcatAg)
{
  _validType = grb::type::HEASARC_GRBCATAG;
  _product = _factory.createType(_validType);
  ASSERT_EQ(nullptr, _product);
}

} // namespace testing
