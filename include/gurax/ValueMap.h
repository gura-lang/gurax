//==============================================================================
// ValueMap.h
//==============================================================================
#ifndef GURAX_VALUEMAP_H
#define GURAX_VALUEMAP_H
#include "Value.h"

namespace Gurax {

//------------------------------------------------------------------------------
// ValueMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ValueMap :
	public std::unordered_map<const Symbol*, Value*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueMap);
protected:
	~ValueMap() { Clear(); }
public:
	void Clear();
	void Assign(const Symbol* pSymbol, Value* pValue);
	Value* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
