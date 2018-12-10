//==============================================================================
// Tokenizer.h
//==============================================================================
#ifndef GURAX_TOKENIZER_H
#define GURAX_TOKENIZER_H
#include "Referable.h"

namespace Gurax {

//-----------------------------------------------------------------------------
// MagicCommentParser
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE MagicCommentParser {
private:
	enum class Stat {
		Idle, Start, SkipSpace, CodingName,
	};
private:
	Stat _stat;
	String _field;
public:
	MagicCommentParser();
	~MagicCommentParser();
	bool ParseChar(char ch);
	const char* GetEncoding() const { return _field.c_str(); }
};

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tokenizer : public Referable {
public:
	enum class Stat {
		BOF, BOF_2nd, BOF_3rd,
		Start,
		White,
		DoubleChars, TripleChars, Escape,
		Colon,
		Error, ErrorRecovery,
		AfterLBrace,
		NumberPre, NumberHex, NumberOct, NumberBin,
		NumberAfterPeriod, Number,
		NumberExpAfterE, NumberExpAfterSign, NumberExp,
		NumberSuffixed,
		Symbol, SymbolExclamation,
		CommentLineTop, CommentLine, MagicCommentLine,
		ShebangLine,
		CommentBlock, CommentBlockEnd, CommentBlockNest,
		StringFirst, StringSecond,
		String, MString, MStringWise, MStringLineHead,
		StringEsc, StringEscHex, StringEscOct, StringEscUnicode,
		StringInCommentBlock, StringEscInCommentBlock,
		MStringEndFirst, MStringEndSecond,
		StringPost, StringSuffixed,
		RecoverConsole,
	};
#if 0
	class GURAX_DLLDECLARE TokenWatcher {
	public:
		virtual void FeedToken(const Token& token) = 0;
	};
#endif
	struct StringInfo {
		char chBorder;
		bool rawFlag;		// prefixed by 'r' or 'R'
		bool binaryFlag;	// prefixed by 'b' or 'B'
		bool wiseFlag;		// prefixed by 'R'
		bool embedFlag;		// prefixed by 'e'
		Stat statRtn;
		int cntRest;
		UInt32 accum;
		String strIndentRef;
	};
private:
#if 0
	Stat _stat;
	bool _lineHeadFlag;
	MagicCommentParser _magicCommentParser;
	bool _appearShebangFlag;
	bool _blockParamFlag;
	int _cntLine;
	int _cntCol;
	int _commentNestLevel;
	//AutoPtr<StringShared> _pSourceName;
	String _field;
	String _strSource;
	String _suffix;
	ExprOwner *_pExprOwner;
	const Expr *_pExprParent;
	//const TokenInfo *_pTokenInfoPrev;
	int _lineNoTop;
	int _lineNoOfTokenPrev;
	//TokenStack _tokenStack;
	StringInfo _stringInfo;
	//CharConverter _charConverter;
	String _strIndent;
	bool _enablePreparatorFlag;
	bool _interactiveFlag;
	//TokenWatcher *_pTokenWatcher;
#endif
public:
	// Constructor
	Tokenizer() = delete;
	// Copy constructor/operator
	Tokenizer(const Tokenizer& src) = delete;
	Tokenizer& operator=(const Tokenizer& src) = delete;
	// Move constructor/operator
	Tokenizer(Tokenizer&& src) = delete;
	Tokenizer& operator=(Tokenizer&& src) noexcept = delete;
protected:
	// Destructor
	~Tokenizer() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(Tokenizer);
public:
	Tokenizer(const String &sourceName, int cntLineStart, bool enablePreparatorFlag);
	bool ParseChar(char ch);
};

}

#endif
