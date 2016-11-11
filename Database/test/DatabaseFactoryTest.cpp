#include "Database/DatabaseFactory.h"

#include "test/Mock/FactoryTestFixtures.h"

namespace testing
{

class DatabaseFactoryTest :
    public FactoryTestFixturesBase<grb::type::DatabaseType, grb::Database, grb::factory::DatabaseFactory>
{
protected:
  void SetUp()
  {
    _invalidType = grb::type::UNDEFINED_DATABASE;
    _invalidName = "undefined-database-table";
  }
};

} // namespace testing

FACTORY_TEST_FIXTURES(DatabaseFactoryTest)

namespace testing
{

TEST_F(DatabaseFactoryTest, createName_DatabaseFormatGrbcat)
{
  _validType = grb::type::HEASARC_GRBCAT;
  _validName = "heasarc_grbcat";
  callCreateName();
}

TEST_F(DatabaseFactoryTest, createType_DatabaseFormatGrbcat)
{
  _validType = grb::type::HEASARC_GRBCAT;
  callCreateType();
}

TEST_F(DatabaseFactoryTest, createType_DatabaseFormatGrbcatAg)
{
  _validType = grb::type::HEASARC_GRBCATAG;
  _product = _factory.createType(_validType);
  ASSERT_EQ(nullptr, _product);
}

} // namespace testing
