//==============================================================================
// StringStyle.h
//==============================================================================
#ifndef GURAX_STRINGSTYLE_H
#define GURAX_STRINGSTYLE_H
#include "String.h"

namespace Gurax {

class Function;
class Argument;

//------------------------------------------------------------------------------
// StringStyle
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE StringStyle {
public:
	using Flags = UInt32;
	struct Flag {
		static const Flags None				= 0;
		static const Flags Bracket			= (1 << 0);
		static const Flags Unbracket		= (1 << 1);
		static const Flags QuoteString		= (1 << 2);
		static const Flags QuoteSymbol		= (1 << 3);
		static const Flags Quote			= QuoteString | QuoteSymbol;
		static const Flags DQuoteString		= (1 << 4);
		static const Flags NilVisible		= (1 << 5);
		static const Flags UndefVisible		= (1 << 6);
		static const Flags InvalidVisible	= NilVisible | UndefVisible;
		static const Flags Cram				= (1 << 7);
		static const Flags MultiLine		= (1 << 8);
		static const Flags Verbose			= (1 << 9);
		static const Flags WithSquare		= (1 << 10);
		static const Flags WithParenthesis	= (1 << 11);
		static const Flags Brief			= (1 << 12);
	};
private:
	Flags _flags;
	String _margin;
	String _indentUnit;
	static const char* _strsComma[2];
	static const char* _strsColon[2];
	static const char* _strsSemicolon[2];
public:
	static const StringStyle Empty;
	static const StringStyle BracketCram;
	static const StringStyle Brief;
	static const StringStyle BriefCram;
	static const StringStyle Unbracket;
	static const StringStyle QuoteString;
	static const StringStyle QuoteSymbol;
	static const StringStyle Quote_NilVisible;
	static const StringStyle Quote_InvalidVisible;
	static const StringStyle Cram;
public:
	// Constructor
	explicit StringStyle(Flags flags = Flag::None, const char* indentUnit = "  ") :
		_flags(flags), _indentUnit(indentUnit) {}
	// Copy constructor/operator
	StringStyle(const StringStyle& src) : _flags(src._flags), _indentUnit(src._indentUnit) {}
	StringStyle& operator=(const StringStyle& src) {
		_flags = src._flags; _indentUnit = src._indentUnit; return *this;
	}
	// Move constructor/operator
	StringStyle(StringStyle&& src) = delete;
	StringStyle& operator=(StringStyle&& src) noexcept = delete;
	// Destructor
	virtual ~StringStyle() = default;
public:	
	StringStyle& SetMargin(const char* margin) { _margin = margin; return *this; }
	StringStyle& SetIndentUnit(const char* indentUnit) { _indentUnit = indentUnit; return *this; }
	StringStyle& SetBracket()			{ _flags |= Flag::Bracket; return *this; }
	StringStyle& UnsetBracket()			{ _flags &= ~Flag::Bracket; return *this; }
	StringStyle& SetUnbracket()			{ _flags |= Flag::Unbracket; return *this; }
	StringStyle& UnsetUnbracket()		{ _flags &= ~Flag::Unbracket; return *this; }
	StringStyle& SetQuoteString()		{ _flags |= Flag::QuoteString; return *this; }
	StringStyle& UnsetQuoteString()		{ _flags &= ~Flag::QuoteString; return *this; }
	StringStyle& SetQuoteSymbol()		{ _flags |= Flag::QuoteSymbol; return *this; }
	StringStyle& UnsetQuoteSymbol()		{ _flags &= ~Flag::QuoteSymbol; return *this; }
	StringStyle& SetQuote()				{ _flags |= Flag::Quote; return *this; }
	StringStyle& UnsetQuote()			{ _flags &= Flag::Quote; return *this; }
	StringStyle& SetDQuoteString()		{ _flags |= Flag::DQuoteString; return *this; }
	StringStyle& UnsetDQuoteString()		{ _flags &= ~Flag::DQuoteString; return *this; }
	StringStyle& SetNilVisible()		{ _flags |= Flag::NilVisible; return *this; }
	StringStyle& UnsetNilVisible()		{ _flags &= ~Flag::NilVisible; return *this; }
	StringStyle& SetUndefVisible()		{ _flags |= Flag::UndefVisible; return *this; }
	StringStyle& UnsetUndefVisible()	{ _flags &= ~Flag::UndefVisible; return *this; }
	StringStyle& SetInvalidVisible()	{ _flags |= Flag::InvalidVisible; return *this; }
	StringStyle& UnsetInvalidVisible()	{ _flags &= ~Flag::InvalidVisible; return *this; }
	StringStyle& SetCram()				{ _flags |= Flag::Cram; return *this; }
	StringStyle& UnsetCram()			{ _flags &= ~Flag::Cram; return *this; }
	StringStyle& SetMultiLine()			{ _flags |= Flag::MultiLine; return *this; }
	StringStyle& UnsetMultiLine()		{ _flags &= ~Flag::MultiLine; return *this; }
	StringStyle& SetVerbose()			{ _flags |= Flag::Verbose; return *this; }
	StringStyle& UnsetVerbose()			{ _flags &= ~Flag::Verbose; return *this; }
	StringStyle& SetWithSquare()		{ _flags |= Flag::WithSquare; return *this; }
	StringStyle& UnsetWithSquare()		{ _flags &= ~Flag::WithSquare; return *this; }
	StringStyle& SetWithParenthesis()	{ _flags |= Flag::WithParenthesis; return *this; }
	StringStyle& UnsetWithParenthesis()	{ _flags &= ~Flag::WithParenthesis; return *this; }
	StringStyle& SetBrief()				{ _flags |= Flag::Brief; return *this; }
	StringStyle& UnsetBrief()			{ _flags &= ~Flag::Brief; return *this; }
	bool IsBracket() const				{ return (_flags & Flag::Bracket) != 0; }
	bool IsUnbracket() const			{ return (_flags & Flag::Unbracket) != 0; }
	bool IsQuoteString() const			{ return (_flags & Flag::QuoteString) != 0; }
	bool IsQuoteSymbol() const			{ return (_flags & Flag::QuoteSymbol) != 0; }
	bool IsDQuoteString() const			{ return (_flags & Flag::DQuoteString) != 0; }
	bool IsNilVisible() const			{ return (_flags & Flag::NilVisible) != 0; }
	bool IsUndefVisible() const			{ return (_flags & Flag::UndefVisible) != 0; }
	bool IsInvalidVisible() const		{ return (_flags & Flag::InvalidVisible) != 0; }
	bool IsCram() const					{ return (_flags & Flag::Cram) != 0; }
	bool IsMultiLine() const			{ return (_flags & Flag::MultiLine) != 0; }
	bool IsVerbose() const				{ return (_flags & Flag::Verbose) != 0; }
	bool IsWithSquare() const			{ return (_flags & Flag::WithSquare) != 0; }
	bool IsWithParenthesis() const		{ return (_flags & Flag::WithParenthesis) != 0; }
	bool IsBrief() const				{ return (_flags & Flag::Brief) != 0; }
	const char* GetMargin() const		{ return _margin.c_str(); }
	const char* GetIndentUnit() const	{ return _indentUnit.c_str(); }
	const char* GetComma() const		{ return _strsComma[static_cast<int>(IsCram())]; }
	const char* GetColon() const		{ return _strsColon[static_cast<int>(IsCram())]; }
	const char* GetSemicolon() const	{ return _strsSemicolon[static_cast<int>(IsCram())]; }
	const char* GetOpening() const		{ return IsWithSquare()? "[" : IsWithParenthesis()? "(" : ""; }
	const char* GetClosing() const		{ return IsWithSquare()? "]" : IsWithParenthesis()? ")" : ""; }
	String MakeIndent(int indentLevel) const;
public:
	static void DeclareAttrOpt(Function& func);
	static Flags ToFlags(const Argument& argument);
};

}

#endif
