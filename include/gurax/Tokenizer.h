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
	// Referable declaration
	Gurax_DeclareReferable(Tokenizer);
public:
	class GURAX_DLLDECLARE TokenWatcher {
	public:
		virtual void FeedToken(RefPtr<Token> pToken) = 0;
	};
private:
	class MagicCommentParser {
	private:
		enum class Stat {
			Idle, Start, SkipSpace, CodingName,
		};
	private:
		Stat _stat;
		String _segment;
	public:
		MagicCommentParser() : _stat(Stat::Start) {}
		bool FeedChar(char ch);
		const char* GetEncoding() const { return _segment.c_str(); }
	};
	enum class Stat {
		BOF, BOF_2nd, BOF_3rd,
		Start,
		White,
		DoubleChars, TripleChars, Escape,
		Colon,
		Error, ErrorRecovery,
		AfterLBrace,
		NumberPre,
		NumberHex, NumberHexUBar,
		NumberOct, NumberOctUBar,
		NumberBin, NumberBinUBar,
		Number, NumberUBar,
		NumberAfterPeriod,
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
	enum class StringType {
		String,
		Binary,					// prefixed by 'b'
		BinaryWritable,			// prefixed by 'B'
		Template,				// prefixed by 'T'
		TmplEmbedded,			// prefixed by 'e'
	};
	struct StringInfo {
		char chBorder;
		bool rawFlag;			// prefixed by 'r' or 'R'
		bool wiseFlag;			// prefixed by 'R'
		StringType type;
		Stat statRtn;
		int cntRest;
		UInt32 accum;
		String strIndentRef;
	};
private:
	TokenWatcher& _tokenWatcher;
	RefPtr<StringReferable> _pPathNameSrc;
	RefPtr<TokenStack> _pTokenStack;
	Stat _stat = Stat::BOF;
	bool _lineHeadFlag = true;
	bool _appearShebangFlag = false;
	bool _blockParamFlag = false;
	int _cntLine = 0;
	int _cntCol = 0;
	int _commentNestLevel = 0;
	int _lineNoTop = 0;
	int _lineNoBodyTop = 0;
	bool _verboseFlag = false;
	String _segment;
	String _source;
	String _suffix;
	StringInfo _stringInfo;
	String _strIndent;
	MagicCommentParser _magicCommentParser;
public:
	// Constructor
	Tokenizer() = delete;
	Tokenizer(TokenWatcher& tokenWatcher, StringReferable* pPathNameSrc);
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
	void RecoverError();
	void FeedChar(char ch);
	void SetCntLine(int cntLine) { _cntLine = cntLine; }
	void SetVerboseFlag(bool verboseFlag) { _verboseFlag = verboseFlag; }
	int GetLineNo() const { return _cntLine + 1; }
	const char* GetPathNameSrc() const { return _pPathNameSrc->GetString(); }
	const String& GetPathNameSrcSTL() const { return _pPathNameSrc->GetStringSTL(); }
	const StringReferable& GetPathNameSrcReferable() const { return *_pPathNameSrc; }
	template<typename... Args>
	void IssueError(const ErrorType& errorType, const char* format, const Args&... args) {
		Error::IssueAt(errorType, GetPathNameSrcReferable().Reference(),
					GetLineNo(), GetLineNo(), format, args...);
	}
	TokenStack& GetTokenStack() { return *_pTokenStack; }
	static bool CheckStringPrefix(StringInfo& stringInfo, const String& field);
};

}

#endif
