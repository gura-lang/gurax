//==============================================================================
// PropHandler.h
//==============================================================================
#ifndef GURAX_PROPHANDLER_H
#define GURAX_PROPHANDLER_H
#include "Attribute.h"
#include "Symbol.h"

namespace Gurax {

//------------------------------------------------------------------------------
// PropHandler
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PropHandler : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PropHandler);
private:
	const Symbol* _pSymbol;
public:
	// Constructor
	PropHandler(const Symbol* pSymbol) : _pSymbol(pSymbol) {}
	// Copy constructor/operator
	PropHandler(const PropHandler& src) : _pSymbol(src._pSymbol) {}
	PropHandler& operator=(const PropHandler& src) = delete;
	// Move constructor/operator
	PropHandler(PropHandler&& src) = delete;
	PropHandler& operator=(PropHandler&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~PropHandler() = default;
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
public:
	// Virtual functions
	virtual Value* DoGetValue(const Value* pValueTarget, const Attribute& attr) const = 0;
	virtual void DoPutValue(Value* pValueTarget, const Value* pValue, const Attribute& attr) const = 0;
};

//------------------------------------------------------------------------------
// PropHandlerMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PropHandlerMap :
	public std::unordered_map<const Symbol*, PropHandler*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PropHandlerMap);
protected:
	~PropHandlerMap() { Clear(); }
public:
	void Clear();
	void Assign(PropHandler* pPropHandler);
	PropHandler* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
