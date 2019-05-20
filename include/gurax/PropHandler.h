//==============================================================================
// PropHandler.h
//==============================================================================
#ifndef GURAX_PROPHANDLER_H
#define GURAX_PROPHANDLER_H
#include "Attribute.h"
#include "Symbol.h"

//------------------------------------------------------------------------------
// Macros to declare PropHandler for instance
//------------------------------------------------------------------------------
#define Gurax_DeclarePropertyAlias_R(nameVType, name, strName)	\
class PropHandler_##nameVType##_##name : public PropHandler { \
public: \
	PropHandler_##nameVType##_##name(const char* name_ = strName); \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override {} \
}; \
PropHandler_##nameVType##_##name::PropHandler_##nameVType##_##name(const char* name_) : \
	PropHandler(name_, Flag::Readable)

#define Gurax_DeclareProperty_R(nameVType, name) Gurax_DeclarePropertyAlias_R(nameVType, name, #name)

#define Gurax_DeclarePropertyAlias_RW(nameVType, name, strName)	\
class PropHandler_##nameVType##_##name : public PropHandler { \
public: \
	PropHandler_##nameVType##_##name(const char* name_ = strName); \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override; \
}; \
PropHandler_##nameVType##_##name::PropHandler_##nameVType##_##name(const char* name_) : \
	PropHandler(name_, Flag::Readable | Flag::Writable)

#define Gurax_DeclareProperty_RW(nameVType, name) Gurax_DeclarePropertyAlias_RW(nameVType, name, #name)

#define Gurax_ImplementPropertyGetter(nameVType, name) \
Value* PropHandler_##nameVType##_##name::DoGetValue(Value& valueTarget, const Attribute& attr) const

#define Gurax_ImplementPropertySetter(nameVType, name) \
void PropHandler_##nameVType##_##name::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const

#define Gurax_CreateProperty(nameVType, name) (new PropHandler_##nameVType##_##name())

//------------------------------------------------------------------------------
// Macros to declare PropHandler for class
//------------------------------------------------------------------------------
#define Gurax_DeclareClassPropertyAlias_R(nameVType, name, strName)	\
class PropHandler_##nameVType##_##name : public PropHandler { \
public: \
	PropHandler_##nameVType##_##name(const char* name_ = strName); \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override {} \
}; \
PropHandler_##nameVType##_##name::PropHandler_##nameVType##_##name(const char* name_) : \
	PropHandler(name_, Flag::Readable | Flag::OfClass)

#define Gurax_DeclareClassProperty_R(nameVType, name) Gurax_DeclareClassPropertyAlias_R(nameVType, name, #name)

#define Gurax_DeclareClassPropertyAlias_RW(nameVType, name, strName)	\
class PropHandler_##nameVType##_##name : public PropHandler { \
public: \
	PropHandler_##nameVType##_##name(const char* name_ = strName); \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override; \
}; \
PropHandler_##nameVType##_##name::PropHandler_##nameVType##_##name(const char* name_) : \
	PropHandler(name_, Flag::Readable | Flag::Writable | Flag::OfClass)

#define Gurax_DeclareClassProperty_RW(nameVType, name) Gurax_DeclareClassPropertyAlias_RW(nameVType, name, #name)

#define Gurax_ImplementClassPropertyGetter(nameVType, name) \
Value* PropHandler_##nameVType##_##name::DoGetValue(Value& valueTarget, const Attribute& attr) const

#define Gurax_ImplementClassPropertySetter(nameVType, name) \
void PropHandler_##nameVType##_##name::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const

#define Gurax_CreateClassProperty(nameVType, name) (new PropHandler_##nameVType##_##name())

//------------------------------------------------------------------------------
// Macros to declare PropHandler for module
//------------------------------------------------------------------------------
#define Gurax_DeclareModulePropertyAlias_R(name, strName)	\
class PropHandler_##name : public PropHandler { \
public: \
	PropHandler_##name(const char* name_ = strName); \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override {} \
}; \
PropHandler_##name::PropHandler_##name(const char* name_) : \
	PropHandler(name_, Flag::Readable)

#define Gurax_DeclareModuleProperty_R(name) Gurax_DeclareModulePropertyAlias_R(name, #name)

#define Gurax_DeclareModulePropertyAlias_RW(name, strName)	\
class PropHandler_##name : public PropHandler { \
public: \
	PropHandler_##name(const char* name_ = strName); \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override; \
}; \
PropHandler_##name::PropHandler_##name(const char* name_) : \
	PropHandler(name_, Flag::Readable | Flag::Writable)

#define Gurax_DeclareModuleProperty_RW(name) Gurax_DeclareModulePropertyAlias_RW(name, #name)

#define Gurax_ImplementModulePropertyGetter(name) \
Value* PropHandler_##name::DoGetValue(Value& valueTarget, const Attribute& attr) const

#define Gurax_ImplementModulePropertySetter(name) \
void PropHandler_##name::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const

#define Gurax_CreateModuleProperty(name) (new PropHandler_##name())

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
		static const Flags ListVar			= (1 << 2);
		static const Flags OfClass			= (1 << 3);
		static const Flags Nil				= (1 << 4);
	};
private:
	const Symbol* _pSymbol;
	const VType* _pVType;
	Flags _flags;
	RefPtr<HelpProvider> _pHelpProvider;
public:
	// Constructor
	PropHandler(const Symbol* pSymbol, Flags flags);
	PropHandler(const char* name, Flags flags) : PropHandler(Symbol::Add(name), flags) {}
	// Copy constructor/operator
	PropHandler(const PropHandler& src) = delete;
	PropHandler& operator=(const PropHandler& src) = delete;
	// Move constructor/operator
	PropHandler(PropHandler&& src) = delete;
	PropHandler& operator=(PropHandler&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~PropHandler() = default;
public:
	void Declare(const VType& vtype, UInt32 flags) { _pVType = &vtype, _flags |= flags; }
	void AddHelp(const Symbol* pLangCode, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(doc));
	}
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	const Symbol* GetSymbol() const { return _pSymbol; }
	const VType& GetVType() const { return *_pVType; }
	const Flags GetFlags() const { return _flags; }
	bool IsSet(Flags flags) const { return (GetFlags() & flags) != 0; }
	Value* GetValue(Value& valueTarget, const Attribute& attr) const {
		return DoGetValue(valueTarget, attr);
	}
	bool SetValue(Value& valueTarget, const Value& value, const Attribute& attr) const;
protected:
	// Virtual functions
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const = 0;
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const = 0;
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
