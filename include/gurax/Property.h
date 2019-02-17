//==============================================================================
// Property.h
//==============================================================================
#ifndef GURAX_PROPERTY_H
#define GURAX_PROPERTY_H
#include "Attribute.h"
#include "Symbol.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Property
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Property : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Property);
public:
	// Constructor
	Property() = default;
	// Copy constructor/operator
	Property(const Property& src) {}
	Property& operator=(const Property& src) = delete;
	// Move constructor/operator
	Property(Property&& src) = delete;
	Property& operator=(Property&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Property() = default;
};

//------------------------------------------------------------------------------
// PropertyMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PropertyMap :
	public std::unordered_map<const Symbol*, Property*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PropertyMap);
protected:
	~PropertyMap() { Clear(); }
public:
	void Clear();
	void Assign(const Symbol* pSymbol, Property* pProperty);
	Property* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
