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
		static const Flags StringUnquoted	= (1 << 0);
		static const Flags SymbolQuoted		= (1 << 1);
		static const Flags NilVisible		= (1 << 2);
		static const Flags Cram				= (1 << 3);
		static const Flags MultiLine		= (1 << 4);
		static const Flags UpperCase		= (1 << 5);
		static const Flags Verbose			= (1 << 6);
		static const Flags AddrInfo			= (1 << 7);
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
	static const StringStyle StringUnquoted;
	static const StringStyle SymbolQuoted;
	static const StringStyle SymbolQuoted_NilVisible;
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
	StringStyle& SetStringUnquoted()	{ _flags |= Flag::StringUnquoted; return *this; }
	StringStyle& UnsetStringUnquoted()	{ _flags &= ~Flag::StringUnquoted; return *this; }
	StringStyle& SetSymbolQuoted()		{ _flags |= Flag::SymbolQuoted; return *this; }
	StringStyle& UnsetSymbolQuoted()	{ _flags &= ~Flag::SymbolQuoted; return *this; }
	StringStyle& SetNilVisible()		{ _flags |= Flag::NilVisible; return *this; }
	StringStyle& UnsetNilVisible()		{ _flags &= ~Flag::NilVisible; return *this; }
	StringStyle& SetCram()				{ _flags |= Flag::Cram; return *this; }
	StringStyle& UnsetCram()			{ _flags &= ~Flag::Cram; return *this; }
	StringStyle& SetMultiLine()			{ _flags |= Flag::MultiLine; return *this; }
	StringStyle& UnsetMultiLine()		{ _flags &= ~Flag::MultiLine; return *this; }
	StringStyle& SetUpperCase()			{ _flags |= Flag::UpperCase; return *this; }
	StringStyle& UnsetUpperCase()		{ _flags &= ~Flag::UpperCase; return *this; }
	StringStyle& SetVerbose()			{ _flags |= Flag::Verbose; return *this; }
	StringStyle& UnsetVerbose()			{ _flags &= ~Flag::Verbose; return *this; }
	StringStyle& SetAddressInfo()		{ _flags |= Flag::AddrInfo; return *this; }
	StringStyle& UnsetAddressInfo()		{ _flags &= ~Flag::AddrInfo; return *this; }
	bool IsStringUnquoted() const		{ return (_flags & Flag::StringUnquoted) != 0; }
	bool IsSymbolQuoted() const			{ return (_flags & Flag::SymbolQuoted) != 0; }
	bool IsNilVisible() const			{ return (_flags & Flag::NilVisible) != 0; }
	bool IsCram() const					{ return (_flags & Flag::Cram) != 0; }
	bool IsMultiLine() const			{ return (_flags & Flag::MultiLine) != 0; }
	bool IsUpperCase() const			{ return (_flags & Flag::UpperCase) != 0; }
	bool IsVerbose() const				{ return (_flags & Flag::Verbose) != 0; }
	bool IsAddressInfo() const			{ return (_flags & Flag::AddrInfo) != 0; }
	const char* GetMargin() const		{ return _margin.c_str(); }
	const char* GetIndentUnit() const	{ return _indentUnit.c_str(); }
	const char* GetComma() const		{ return _strsComma[static_cast<int>(IsCram())]; }
	const char* GetColon() const		{ return _strsColon[static_cast<int>(IsCram())]; }
	const char* GetSemicolon() const	{ return _strsSemicolon[static_cast<int>(IsCram())]; }
public:
	static void DeclareAttrOpt(Function& func);
	static Flags ToFlags(const Argument& argument);
};

}

#endif
