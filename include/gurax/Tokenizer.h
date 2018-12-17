//==============================================================================
// Tokenizer.h
//==============================================================================
#ifndef GURAX_TOKENIZER_H
#define GURAX_TOKENIZER_H
#include "Token.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Tokenizer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tokenizer : public Referable {
public:
	class GURAX_DLLDECLARE TokenWatcher {
	public:
		virtual void FeedToken(UniquePtr<Token> pToken) = 0;
	};
private:
	class MagicCommentParser {
	private:
		enum class Stat {
			Idle, Start, SkipSpace, CodingName,
		};
	private:
		Stat _stat;
		String _value;
	public:
		MagicCommentParser() : _stat(Stat::Start) {}
		bool FeedChar(char ch);
		const char* GetEncoding() const { return _value.c_str(); }
	};
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
	TokenWatcher& _tokenWatcher;
	StringShared _pPathNameSrc;
	Stat _stat = Stat::BOF;
	bool _lineHeadFlag = true;
	bool _appearShebangFlag = false;
	bool _blockParamFlag = false;
	int _cntLine = 0;
	int _cntCol = 0;
	int _commentNestLevel = 0;
	int _lineNoTop = 0;
	bool _verboseFlag = false;
	String _value;
	String _strSource;
	String _suffix;
	TokenStack _tokenStack;
	StringInfo _stringInfo;
	String _strIndent;
	MagicCommentParser _magicCommentParser;
	//CharConverter _charConverter;
	//ExprOwner *_pExprOwner;
	//const Expr *_pExprParent;
	//const TokenType *_pTokenTypePrev;
	//int _lineNoOfTokenPrev;
	//bool _interactiveFlag;
	//bool _enablePreparatorFlag;
public:
	// Constructor
	Tokenizer() = delete;
	Tokenizer(TokenWatcher& tokenWatcher, String pathNameSrc);
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
	void InitStack();
	bool FeedChar(char ch);
	void SetCntLine(int cntLine) { _cntLine = cntLine; }
	void SetVerboseFlag(bool verboseFlag) { _verboseFlag = verboseFlag; }
	int GetLineNo() const { return _cntLine + 1; }
	const char* GetPathNameSrc() const { return _pPathNameSrc->c_str(); }
	const StringShared& GetPathNameSrcShared() const { return _pPathNameSrc; }
	void IssueError(const ErrorType& errorType, const char* format, ...);
	TokenStack &GetTokenStack() { return _tokenStack; }
	static const TokenType& GetTokenTypeForString(const StringInfo& stringInfo);
	static bool CheckStringPrefix(StringInfo& stringInfo, const String& field);
};

}

#endif
