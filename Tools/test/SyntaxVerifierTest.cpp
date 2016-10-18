#include "Tools/SyntaxVerifier.h"

#include <gmock/gmock.h>

namespace testing
{

class SyntaxVerifierTest : public Test
{
protected:
  void TearDown()
  {
    delete _verifier;
  }

  grb::SyntaxVerifier* _verifier;
  std::list<std::string> _tokens;

};

TEST_F(SyntaxVerifierTest, constructByList)
{
  _verifier = new grb::SyntaxVerifier(_tokens);
}

TEST_F(SyntaxVerifierTest, constructByIterator)
{
  _verifier = new grb::SyntaxVerifier(_tokens.begin(), _tokens.end());
}

TEST_F(SyntaxVerifierTest, verifyRange_InvalidLeftBraket)
{
  _tokens = { "[", "0.0", ",", "1.0", ")" };
  _verifier = new grb::SyntaxVerifier(_tokens);
  ASSERT_FALSE(_verifier->verifyRange());
  ASSERT_TRUE(_verifier->getExtracted().empty());
}

TEST_F(SyntaxVerifierTest, verifyRange_InvalidRightBraket)
{
  _tokens = { "(", "0.0", ",", "1.0", "]" };
  _verifier = new grb::SyntaxVerifier(_tokens);
  ASSERT_FALSE(_verifier->verifyRange());
  ASSERT_TRUE(_verifier->getExtracted().empty());
}

TEST_F(SyntaxVerifierTest, verifyRange_InvalidComma)
{
  _tokens = { "(", "0.0", "-", "1.0", ")" };
  _verifier = new grb::SyntaxVerifier(_tokens);
  ASSERT_FALSE(_verifier->verifyRange());
  ASSERT_TRUE(_verifier->getExtracted().empty());
}

TEST_F(SyntaxVerifierTest, verifyRange_EmptyMinValue)
{
  _tokens = { "(", "", ",", "1.0", ")" };
  _verifier = new grb::SyntaxVerifier(_tokens);
  ASSERT_FALSE(_verifier->verifyRange());
  ASSERT_TRUE(_verifier->getExtracted().empty());
}

TEST_F(SyntaxVerifierTest, verifyRange_EmptyMaxValue)
{
  _tokens = { "(", "0.0", ",", "", ")" };
  _verifier = new grb::SyntaxVerifier(_tokens);
  ASSERT_FALSE(_verifier->verifyRange());
  ASSERT_TRUE(_verifier->getExtracted().empty());
}

TEST_F(SyntaxVerifierTest, verifyRange_NoTokens)
{
  _verifier = new grb::SyntaxVerifier(_tokens);
  ASSERT_FALSE(_verifier->verifyRange());
  ASSERT_TRUE(_verifier->getExtracted().empty());
}

TEST_F(SyntaxVerifierTest, verifyRange_LessTokens)
{
  _tokens = { "(", "0.0", ",", "1.0", };
  _verifier = new grb::SyntaxVerifier(_tokens);
  ASSERT_FALSE(_verifier->verifyRange());
  ASSERT_TRUE(_verifier->getExtracted().empty());
}

TEST_F(SyntaxVerifierTest, verifyRange_MoreTokens)
{
  _tokens = { "(", "0.0", ",", "1.0", ")", "extra" };
  _verifier = new grb::SyntaxVerifier(_tokens);
  ASSERT_FALSE(_verifier->verifyRange());
  ASSERT_TRUE(_verifier->getExtracted().empty());
}

TEST_F(SyntaxVerifierTest, verifyRange_AllTokensWrong)
{
  _tokens = { "-", "", "-", "", "-" };
  _verifier = new grb::SyntaxVerifier(_tokens);
  ASSERT_FALSE(_verifier->verifyRange());
  ASSERT_TRUE(_verifier->getExtracted().empty());
}

TEST_F(SyntaxVerifierTest, verifyRange_Positive)
{
  _tokens = { "(", "0.0", ",", "1.0", ")" };
  _verifier = new grb::SyntaxVerifier(_tokens);
  ASSERT_TRUE(_verifier->verifyRange());
  ASSERT_STREQ("0.0", _verifier->getExtracted()[0]->c_str());
  ASSERT_STREQ("1.0", _verifier->getExtracted()[1]->c_str());
}


} // namespace testing
