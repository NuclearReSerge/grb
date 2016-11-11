#include "Correlation/CorrelationTimeArcGrbcat.h"

#include "test/Mock/CatalogMock.h"
#include "test/Mock/MockHelper.h"

#include <gmock/gmock.h>

namespace testing
{

class CorrelationTimeArcGrbcatTest : public Test
{
protected:
  void SetUp()
  {
    _tokens = { "set-params", "default"};
  }

  void tryToParse()
  {
    try
    {
      _result = _corr.parse(_cmd, _tokens);
    }
    catch (grb::Exception& exc)
    {
      _thrown = true;
      printWhat(exc);
    }
  }

  bool _result = false;
  bool _thrown = false;

  std::list<std::string> _tokens;
  grb::CatalogMock _catalogData { grb::type::UNDEFINED_CATALOG };
  grb::CatalogMock _catalogModel { grb::type::UNDEFINED_CATALOG };
  std::string _filePrefix;

  grb::CorrelationTimeArcGrbcat _corr;
  grb::type::CorrelationCmdType _cmd;

};

TEST_F(CorrelationTimeArcGrbcatTest, init)
{
  ASSERT_EQ(grb::type::CORRELATION_GRBCAT_DTDARC, _corr.getType());
}

TEST_F(CorrelationTimeArcGrbcatTest, Parse_EmptyTokens)
{
  _tokens.clear();

  tryToParse();

  ASSERT_FALSE(_result);
}

TEST_F(CorrelationTimeArcGrbcatTest, Parse_SetParams_Default)
{

  tryToParse();

  ASSERT_FALSE(_result);
}



} // namespace testing
