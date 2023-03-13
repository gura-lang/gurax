//==============================================================================
// Tokenizer.h
//==============================================================================
#ifndef GURAX_MODULE_MODEL_OBJ_TOKENIZER_H
#define GURAX_MODULE_MODEL_OBJ_TOKENIZER_H
#include <gurax.h>

Gurax_BeginModuleScope(model_obj)

enum class TokenId {
	None, EndOfLine, EndOfFile, Field,
};

class Tokenizer {
public:
	enum class Stat { LineTop, SkipToNextLine, Field, SkipWhite, EndOfFile, };
private:
	Stat _stat;
	size_t _iLine;
	size_t _iChar;
	char _field[128];
	TokenId _tokenIdPending;
public:
	Tokenizer() : _stat(Stat::LineTop), _iLine(0), _iChar(0), _tokenIdPending(TokenId::None) {
		_field[0] = '\0';
	}
	TokenId Tokenize(Stream& stream);
	const char* GetField() const { return _field; }
	size_t GetLineNo() const { return _iLine + 1; }
};

Gurax_EndModuleScope(model_obj)

#endif
