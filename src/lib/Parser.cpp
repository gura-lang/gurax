//==============================================================================
// Parser.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Parser
//------------------------------------------------------------------------------
Parser::Parser(String pathNameSrc) : _pTokenizer(new Tokenizer(*this, std::move(pathNameSrc)))
{
}

void Parser::FeedToken(UniquePtr<Token> pToken)
{
}

}
