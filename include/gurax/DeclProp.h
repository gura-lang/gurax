//==============================================================================
// DeclProp.h
//==============================================================================
#ifndef GURAX_DECLPROP_H
#define GURAX_DECLPROP_H
#include "Attribute.h"
#include "Symbol.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclProp
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DeclProp : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DeclProp);
public:
	// Constructor
	DeclProp() = default;
	// Copy constructor/operator
	DeclProp(const DeclProp& src) {}
	DeclProp& operator=(const DeclProp& src) = delete;
	// Move constructor/operator
	DeclProp(DeclProp&& src) = delete;
	DeclProp& operator=(DeclProp&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~DeclProp() = default;
};

//------------------------------------------------------------------------------
// DeclPropMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DeclPropMap :
	public std::unordered_map<const Symbol*, DeclProp*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(DeclPropMap);
protected:
	~DeclPropMap() { Clear(); }
public:
	void Clear();
	void Assign(const Symbol* pSymbol, DeclProp* pDeclProp);
	DeclProp* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
