//==============================================================================
// Symbol.h
//==============================================================================
#ifndef GURAX_SYMBOL_H
#define GURAX_SYMBOL_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Symbol
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Symbol {
public:
	struct LessThan {
		bool operator()(const Symbol* pSymbol1, const Symbol* pSymbol2) {
			return pSymbol1->GetId() < pSymbol2->GetId();
		}
	};
protected:
	int _id;
public:
	// Default constructor
	Symbol() {}
	// Copy constructor/operator
	Symbol(const Symbol& src) = delete;
	Symbol& operator=(const Symbol& src) = delete;
	// Move constructor/operator
	Symbol(Symbol&& src) = delete;
	Symbol& operator=(Symbol&& src) noexcept = delete;
	// Destructor
	~Symbol() = default;
public:
	int GetId() const { return _id; }
};

//------------------------------------------------------------------------------
// SymbolSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SymbolSet :
	public std::set<const Symbol*, Symbol::LessThan>, public Referable {
protected:
	~SymbolSet() = default;
public:
	// Referable accessor
	Gurax_DeclareReferable(SymbolSet);
};

}

#endif
