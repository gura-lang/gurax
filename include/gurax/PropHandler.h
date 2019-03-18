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
public:
	using Flags = UInt32;
	struct Flag {
		static const Flags None				= 0;
		static const Flags Readable			= (1 << 0);
		static const Flags Writable			= (1 << 1);
	};
private:
	const Symbol* _pSymbol;
	const VType* _pVTypeResult;
	Flags _flags;
public:
	// Constructor
	PropHandler(const Symbol* pSymbol, Flags flags);
	PropHandler(const char* name, Flags flags) : PropHandler(Symbol::Add(name), flags) {}
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
	void Declare(const VType& vtypeResult, UInt32 flags) { _pVTypeResult = &vtypeResult, _flags |= flags; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const VType& GetVTypeResult() const { return *_pVTypeResult; }
	const Flags GegFlags() const { return _flags; }
public:
	// Virtual functions
	virtual Value* DoGetValue(const Value& valueTarget, const Attribute& attr) const = 0;
	virtual void DoPutValue(Value& valueTarget, const Value* pValue, const Attribute& attr) const = 0;
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
