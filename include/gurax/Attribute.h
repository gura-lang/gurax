//==============================================================================
// Attribute.h
//==============================================================================
#ifndef GURAX_ATTRIBUTE_H
#define GURAX_ATTRIBUTE_H
#include "Referable.h"
#include "Symbol.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Attribute
//------------------------------------------------------------------------------
class Attribute : public Referable {
private:
	RefPtr<DottedSymbol> _pDottedSymbol;
	SymbolList _symbolList;
	SymbolList _symbolListOpt;
	SymbolSet _symbolSet;
	SymbolSet _symbolSetOpt;
public:
	Gurax_DeclareReferable(Attribute);
public:
	static void Bootup();
public:
	Attribute() {}
protected:
	~Attribute() = default;
public:
	bool IsDottedSymbolSet() const { return _pDottedSymbol.get() != nullptr; }
	void SetDottedSymbol(DottedSymbol* pDottedSymbol) { _pDottedSymbol.reset(pDottedSymbol); }
	const DottedSymbol& GetDottedSymbol() const {
		return _pDottedSymbol? *_pDottedSymbol : DottedSymbol::Empty;
	}
	void AddAttribute(const Attribute& attribute);
	void AddSymbol(const Symbol* pSymbol);
	void AddSymbolOpt(const Symbol* pSymbol) {
		_symbolListOpt.push_back(pSymbol);
		_symbolSetOpt.insert(pSymbol);
	}
	void AddSymbols(const SymbolList& symbolList) {
		for (const Symbol* pSymbol : symbolList) AddSymbol(pSymbol);
	}
	void AddSymbolsOpt(const SymbolList& symbolList) {
		for (const Symbol* pSymbol : symbolList) AddSymbolOpt(pSymbol);
	}
	bool IsSet(const Symbol* pSymbol) { return _symbolSet.IsSet(pSymbol); }
	bool IsSetOpt(const Symbol* pSymbol) { return _symbolSetOpt.IsSet(pSymbol); }
	const SymbolList& GetSymbols() const { return _symbolList; }
	const SymbolList& GetSymbolsOpt() const { return _symbolListOpt; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Attribute* pAttr) const { return this == pAttr; }
	bool IsEqualTo(const Attribute* pAttr) const { return IsIdentical(pAttr); }
	bool IsLessThan(const Attribute* pAttr) const { return this < pAttr; }
	String ToString() const { return "(attribute)"; }
};

}

#endif
