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
class GURAX_DLLDECLARE ValueMap : public Referable {
public:
	using Map = std::unordered_map<const Symbol*, Value*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
private:
	Map _map;
public:
	// Referable declaration
	Gurax_DeclareReferable(ValueMap);
protected:
	~ValueMap() { Clear(); }
public:
	Map& GetMap() { return _map; }
	const Map& GetMap() const { return _map; }
	void Clear();
	void Assign(const Symbol* pSymbol, Value* pValue);
	Value* Lookup(const Symbol* pSymbol) const {
		auto pPair = _map.find(pSymbol);
		return (pPair == _map.end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return _map.find(pSymbol) != _map.end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	bool ExportTo(Frame& frameDst, bool overwriteFlag) const;
	void GatherSymbol(SymbolList& symbolList) const;
	void GatherSymbolIf(SymbolList& symbolList, const Frame::GatherCriteria& gatherCriteria) const;
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
