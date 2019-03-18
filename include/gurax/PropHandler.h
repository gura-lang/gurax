//==============================================================================
// PropHandler.h
//==============================================================================
#ifndef GURAX_PROPHANDLER_H
#define GURAX_PROPHANDLER_H
#include "Attribute.h"
#include "Symbol.h"

//------------------------------------------------------------------------------
// Macros to declare PropHandler
//------------------------------------------------------------------------------
#define Gurax_DeclarePropertyAlias_R(nameVType, name, strName)	\
class PropHandler_##nameVType##_##name : public PropHandler { \
public: \
	PropHandler_##nameVType##_##name(const char* name_ = strName); \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, Value* pValue, const Attribute& attr) const override {} \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
}; \
PropHandler_##nameVType##_##name::PropHandler_##nameVType##_##name(const char* name_) : \
	PropHandler(name_, Flag::Readable)

#define Gurax_DeclareProperty_R(nameVType, name) Gurax_DeclarePropertyAlias_R(nameVType, name, #name)

#define Gurax_DeclarePropertyAlias_RW(nameVType, name, strName)	\
class PropHandler_##nameVType##_##name : public PropHandler { \
public: \
	PropHandler_##nameVType##_##name(const char* name_ = strName); \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, Value* pValue, const Attribute& attr) const override; \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
}; \
PropHandler_##nameVType##_##name::PropHandler_##nameVType##_##name(const char* name_) : \
	PropHandler(name_, Flag::Readable | Flag::Writable)

#define Gurax_DeclareProperty_RW(nameVType, name) Gurax_DeclarePropertyAlias_RW(nameVType, name, #name)

#define Gurax_ImplementPropertyGetter(nameVType, name) \
Value* PropHandler_##nameVType##_##name::DoGetValue(Value& valueTarget, const Attribute& attr) const

#define Gurax_ImplementPropertySetter(nameVType, name) \
void PropHandler_##nameVType##_##name::DoSetValue(Value& valueTarget, Value* pValue, const Attribute& attr) const

#define Gurax_CreateProperty(nameVType, name) (new PropHandler_##nameVType##_##name())

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
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const = 0;
	virtual void DoSetValue(Value& valueTarget, Value* pValue, const Attribute& attr) const = 0;
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
