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
	enum Stat {
		STAT_Idle, STAT_Start, STAT_SkipSpace, STAT_CodingName,
	};
private:
	//Stat _stat;
	String _field;
public:
	MagicCommentParser();
	~MagicCommentParser();
	bool ParseChar(char ch);
	const char *GetEncoding() const { return _field.c_str(); }
};

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tokenizer : public Referable {
public:
	enum Stat {
		STAT_BOF, STAT_BOF_2nd, STAT_BOF_3rd,
		STAT_Start,
		STAT_White,
		STAT_DoubleChars, STAT_TripleChars, STAT_Escape,
		STAT_Colon,
		STAT_Error, STAT_ErrorRecovery,
		STAT_AfterLBrace,
		STAT_NumberPre, STAT_NumberHex, STAT_NumberOct, STAT_NumberBin,
		STAT_NumberAfterPeriod, STAT_Number,
		STAT_NumberExpAfterE, STAT_NumberExpAfterSign, STAT_NumberExp,
		STAT_NumberSuffixed,
		STAT_Symbol, STAT_SymbolExclamation,
		STAT_CommentLineTop, STAT_CommentLine, STAT_MagicCommentLine,
		STAT_ShebangLine,
		STAT_CommentBlock, STAT_CommentBlockEnd, STAT_CommentBlockNest,
		STAT_StringFirst, STAT_StringSecond,
		STAT_String, STAT_MString, STAT_MStringWise, STAT_MStringLineHead,
		STAT_StringEsc, STAT_StringEscHex, STAT_StringEscOct, STAT_StringEscUnicode,
		STAT_StringInCommentBlock, STAT_StringEscInCommentBlock,
		STAT_MStringEndFirst, STAT_MStringEndSecond,
		STAT_StringPost, STAT_StringSuffixed,
		STAT_RecoverConsole,
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
	// Default constructor
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
	Gurax_DeclareReferable(Tokenizer);
public:
	Tokenizer(const String &sourceName, int cntLineStart, bool enablePreparatorFlag);
	bool ParseChar(char ch);
};

}

#endif
