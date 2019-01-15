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
	void AddSymbol(const Symbol* pSymbol);
	void AddSymbolOpt(const Symbol* pSymbol) {
		_symbolListOpt.push_back(pSymbol);
		_symbolSetOpt.insert(pSymbol);
	}
	bool IsDottedSymbolSet() const { return _pDottedSymbol.get() != nullptr; }
	void SetDottedSymbol(DottedSymbol* pDottedSymbol) { _pDottedSymbol.reset(pDottedSymbol); }
	const DottedSymbol& GetDottedSymbol() {
		return _pDottedSymbol? *_pDottedSymbol : DottedSymbol::Empty;
	}
	bool IsSet(const Symbol* pSymbol) { return _symbolSet.IsSet(pSymbol); }
	bool IsSetOpt(const Symbol* pSymbol) { return _symbolSetOpt.IsSet(pSymbol); }
};

}

#endif
