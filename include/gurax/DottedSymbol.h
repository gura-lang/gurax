//==============================================================================
// DottedSymbol.h
//==============================================================================
#ifndef GURAX_DOTTEDSYMBOL_H
#define GURAX_DOTTEDSYMBOL_H
#include "Symbol.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DottedSymbol
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DottedSymbol : public Referable {
private:
	SymbolList _symbolList;
public:
	static const DottedSymbol* Empty;
public:
	// Referable accessor
	Gurax_DeclareReferable(DottedSymbol);
public:
	// Constructor
	DottedSymbol() = default;
	explicit DottedSymbol(const Symbol* pSymbol) {
		_symbolList.reserve(1);
		_symbolList.push_back(pSymbol); 
	}
	DottedSymbol(const Symbol* pSymbol1, const Symbol* pSymbol2) {
		_symbolList.reserve(2);
		_symbolList.push_back(pSymbol1); _symbolList.push_back(pSymbol2);
	}
	DottedSymbol(const Symbol* pSymbol1, const Symbol* pSymbol2, const Symbol* pSymbol3) {
		_symbolList.reserve(3);
		_symbolList.push_back(pSymbol1); _symbolList.push_back(pSymbol2); _symbolList.push_back(pSymbol3);
	}
	DottedSymbol(const Symbol* pSymbol1, const Symbol* pSymbol2, const Symbol* pSymbol3, const Symbol* pSymbol4) {
		_symbolList.reserve(4);
		_symbolList.push_back(pSymbol1); _symbolList.push_back(pSymbol2);
		_symbolList.push_back(pSymbol3); _symbolList.push_back(pSymbol4);
	}
	DottedSymbol(const Symbol* pSymbol1, const Symbol* pSymbol2, const Symbol* pSymbol3,
				 const Symbol* pSymbol4, const Symbol* pSymbol5) {
		_symbolList.reserve(5);
		_symbolList.push_back(pSymbol1); _symbolList.push_back(pSymbol2);
		_symbolList.push_back(pSymbol3); _symbolList.push_back(pSymbol4);
		_symbolList.push_back(pSymbol5);
	}
	DottedSymbol(const Symbol* pSymbol1, const Symbol* pSymbol2, const Symbol* pSymbol3,
				 const Symbol* pSymbol4, const Symbol* pSymbol5, const Symbol* pSymbol6) {
		_symbolList.reserve(6);
		_symbolList.push_back(pSymbol1); _symbolList.push_back(pSymbol2);
		_symbolList.push_back(pSymbol3); _symbolList.push_back(pSymbol4);
		_symbolList.push_back(pSymbol5); _symbolList.push_back(pSymbol6);
	}
	explicit DottedSymbol(const char* str) {
		_symbolList.reserve(1);
		_symbolList.push_back(Symbol::Add(str)); 
	}
	DottedSymbol(const char* str1, const char* str2) {
		_symbolList.reserve(2);
		_symbolList.push_back(Symbol::Add(str1)); _symbolList.push_back(Symbol::Add(str2));
	}
	DottedSymbol(const char* str1, const char* str2, const char* str3) {
		_symbolList.reserve(3);
		_symbolList.push_back(Symbol::Add(str1)); _symbolList.push_back(Symbol::Add(str2));
		_symbolList.push_back(Symbol::Add(str3));
	}
	DottedSymbol(const char* str1, const char* str2, const char* str3, const char* str4) {
		_symbolList.reserve(4);
		_symbolList.push_back(Symbol::Add(str1)); _symbolList.push_back(Symbol::Add(str2));
		_symbolList.push_back(Symbol::Add(str3)); _symbolList.push_back(Symbol::Add(str4));
	}
	DottedSymbol(const char* str1, const char* str2, const char* str3,
				 const char* str4, const char* str5) {
		_symbolList.reserve(5);
		_symbolList.push_back(Symbol::Add(str1)); _symbolList.push_back(Symbol::Add(str2));
		_symbolList.push_back(Symbol::Add(str3)); _symbolList.push_back(Symbol::Add(str4));
		_symbolList.push_back(Symbol::Add(str5));
	}
	DottedSymbol(const char* str1, const char* str2, const char* str3,
				 const char* str4, const char* str5, const char* str6) {
		_symbolList.reserve(6);
		_symbolList.push_back(Symbol::Add(str1)); _symbolList.push_back(Symbol::Add(str2));
		_symbolList.push_back(Symbol::Add(str3)); _symbolList.push_back(Symbol::Add(str4));
		_symbolList.push_back(Symbol::Add(str5)); _symbolList.push_back(Symbol::Add(str6));
	}
	DottedSymbol(const DottedSymbol& src, size_t nSymbols) :
		_symbolList(src._symbolList.begin(), src._symbolList.begin() + nSymbols) {}
	explicit DottedSymbol(std::initializer_list<const Symbol*> initList) : _symbolList(initList) {}
	// Copy constructor/operator
	DottedSymbol(const DottedSymbol& src) : _symbolList(src._symbolList) {}
	DottedSymbol& operator=(const DottedSymbol& src) { _symbolList = src._symbolList; return *this; }
	// Move constructor/operator
	DottedSymbol(DottedSymbol&& src) = delete;
	DottedSymbol& operator=(DottedSymbol&& src) noexcept = delete;
protected:
	// Destructor
	~DottedSymbol() = default;
public:
	static void Bootup();
	const SymbolList& GetSymbolList() const { return _symbolList; }
	const Symbol* GetSymbolFirst() const { return _symbolList.front(); }
	const Symbol* GetSymbolLast() const { return _symbolList.back(); }
	void Reserve(size_t n) { _symbolList.reserve(n); }
	void Append(const Symbol* pSymbol) { _symbolList.push_back(pSymbol); }
	void Append(const char* str) { _symbolList.push_back(Symbol::Add(str)); }
	bool AppendFromExprList(const ExprList& exprList);
	bool AppendFromString(const char* str, char separator = '.');
	bool AppendFromExpr(const Expr& expr);
	Expr* ToExpr() const;
	String ToString(char separator, const StringStyle& ss = StringStyle::Empty) const;
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return ToString('.', ss); }
	size_t GetLength() const { return _symbolList.size(); }
	bool IsSingleSymbol() const { return _symbolList.size() == 1; }
	bool IsDotted() const { return _symbolList.size() > 1; }
	bool IsEmpty() const { return _symbolList.empty(); }
	bool IsEqualTo(const Symbol* pSymbol) const {
		return _symbolList.size() == 1 && _symbolList.front()->IsEqualTo(pSymbol);
	}
	bool IsEqualTo(const DottedSymbol& dottedSymbol) const {
		return _symbolList.IsEqualTo(dottedSymbol.GetSymbolList());
	}
	DottedSymbol* Clone() const { return new DottedSymbol(*this); }
public:
	static DottedSymbol* CreateFromExprList(const ExprList& exprList) {
		RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol());
		return pDottedSymbol->AppendFromExprList(exprList)? pDottedSymbol.release() : nullptr;
	}
	static DottedSymbol* CreateFromString(const char* str, char separator = '.') {
		RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol());
		return pDottedSymbol->AppendFromString(str, separator)? pDottedSymbol.release() : nullptr;
	}
	static DottedSymbol* CreateFromExpr(const Expr& expr) {
		RefPtr<DottedSymbol> pDottedSymbol(new DottedSymbol());
		return pDottedSymbol->AppendFromExpr(expr)? pDottedSymbol.release() : nullptr;
	}
};

}

#endif
