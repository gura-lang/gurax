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
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	Property(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
	// Copy constructor/operator
	Property(const Property& src) : _pSymbol(src._pSymbol) {}
	Property& operator=(const Property& src) = delete;
	// Move constructor/operator
	Property(Property&& src) = delete;
	Property& operator=(Property&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~Property() = default;
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions
	virtual Value* DoGetValue(const Value* pValueTarget, const Attribute& attr) const = 0;
	virtual void DoPutValue(Value* pValueTarget, const Value* pValue, const Attribute& attr) const = 0;
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
	void Assign(Property* pProperty);
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
