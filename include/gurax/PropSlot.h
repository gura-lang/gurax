//==============================================================================
// PropSlot.h
//==============================================================================
#ifndef GURAX_PROPSLOT_H
#define GURAX_PROPSLOT_H
#include "Attribute.h"
#include "Symbols.h"
#include "DeclArg.h"

//------------------------------------------------------------------------------
// Macros to declare PropSlot for instance
//------------------------------------------------------------------------------
#define Gurax_DeclarePropertyAlias_R(nameVType, name, strName)	\
class PropSlot_##nameVType##_##name : public PropSlot { \
public: \
	PropSlot_##nameVType##_##name(const char* name_ = strName); \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override {} \
}; \
PropSlot_##nameVType##_##name::PropSlot_##nameVType##_##name(const char* name_) : \
	PropSlot(name_, Flag::OfInstance | Flag::Readable)

#define Gurax_DeclareProperty_R(nameVType, name) Gurax_DeclarePropertyAlias_R(nameVType, name, #name)

#define Gurax_DeclarePropertyAlias_RW(nameVType, name, strName)	\
class PropSlot_##nameVType##_##name : public PropSlot { \
public: \
	PropSlot_##nameVType##_##name(const char* name_ = strName); \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override; \
}; \
PropSlot_##nameVType##_##name::PropSlot_##nameVType##_##name(const char* name_) : \
	PropSlot(name_, Flag::OfInstance | Flag::Readable | Flag::Writable)

#define Gurax_DeclareProperty_RW(nameVType, name) Gurax_DeclarePropertyAlias_RW(nameVType, name, #name)

#define Gurax_ImplementPropertyGetter(nameVType, name) \
Value* PropSlot_##nameVType##_##name::DoGetValue(Value& valueTarget, const Attribute& attr) const

#define Gurax_ImplementPropertySetter(nameVType, name) \
void PropSlot_##nameVType##_##name::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const

#define Gurax_CreateProperty(nameVType, name) (new PropSlot_##nameVType##_##name())

//------------------------------------------------------------------------------
// Macros to declare PropSlot for class
//------------------------------------------------------------------------------
#define Gurax_DeclareClassPropertyAlias_R(nameVType, name, strName)	\
class PropSlot_##nameVType##_##name : public PropSlot { \
public: \
	PropSlot_##nameVType##_##name(const char* name_ = strName); \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override {} \
}; \
PropSlot_##nameVType##_##name::PropSlot_##nameVType##_##name(const char* name_) : \
PropSlot(name_, Flag::OfClass | Flag::Readable)

#define Gurax_DeclareClassProperty_R(nameVType, name) Gurax_DeclareClassPropertyAlias_R(nameVType, name, #name)

#define Gurax_DeclareClassPropertyAlias_RW(nameVType, name, strName)	\
class PropSlot_##nameVType##_##name : public PropSlot { \
public: \
	PropSlot_##nameVType##_##name(const char* name_ = strName); \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override; \
}; \
PropSlot_##nameVType##_##name::PropSlot_##nameVType##_##name(const char* name_) : \
	PropSlot(name_, Flag::OfClass | Flag::Readable | Flag::Writable)

#define Gurax_DeclareClassProperty_RW(nameVType, name) Gurax_DeclareClassPropertyAlias_RW(nameVType, name, #name)

#define Gurax_ImplementClassPropertyGetter(nameVType, name) \
Value* PropSlot_##nameVType##_##name::DoGetValue(Value& valueTarget, const Attribute& attr) const

#define Gurax_ImplementClassPropertySetter(nameVType, name) \
void PropSlot_##nameVType##_##name::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const

#define Gurax_CreateClassProperty(nameVType, name) (new PropSlot_##nameVType##_##name())

//------------------------------------------------------------------------------
// Macros to declare PropSlot for hybrid
//------------------------------------------------------------------------------
#define Gurax_DeclareHybridPropertyAlias_R(nameVType, name, strName)	\
class PropSlot_##nameVType##_##name : public PropSlot { \
public: \
	PropSlot_##nameVType##_##name(const char* name_ = strName); \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override {} \
}; \
PropSlot_##nameVType##_##name::PropSlot_##nameVType##_##name(const char* name_) : \
PropSlot(name_, Flag::OfClass | Flag::OfInstance | Flag::Readable)

#define Gurax_DeclareHybridProperty_R(nameVType, name) Gurax_DeclareHybridPropertyAlias_R(nameVType, name, #name)

#define Gurax_DeclareHybridPropertyAlias_RW(nameVType, name, strName)	\
class PropSlot_##nameVType##_##name : public PropSlot { \
public: \
	PropSlot_##nameVType##_##name(const char* name_ = strName); \
	static Value_##nameVType& GetValueThis(Value& valueTarget) { \
		return dynamic_cast<Value_##nameVType&>(valueTarget); \
	} \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override; \
}; \
PropSlot_##nameVType##_##name::PropSlot_##nameVType##_##name(const char* name_) : \
PropSlot(name_, Flag::OfClass | Flag::OfInstance | Flag::Readable | Flag::Writable)

#define Gurax_DeclareHybridProperty_RW(nameVType, name) Gurax_DeclareHybridPropertyAlias_RW(nameVType, name, #name)

#define Gurax_ImplementHybridPropertyGetter(nameVType, name) \
Value* PropSlot_##nameVType##_##name::DoGetValue(Value& valueTarget, const Attribute& attr) const

#define Gurax_ImplementHybridPropertySetter(nameVType, name) \
void PropSlot_##nameVType##_##name::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const

#define Gurax_CreateHybridProperty(nameVType, name) (new PropSlot_##nameVType##_##name())

//------------------------------------------------------------------------------
// Macros to declare PropSlot for module
//------------------------------------------------------------------------------
#define Gurax_DeclareModulePropertyAlias_R(name, strName)	\
class PropSlot_##name : public PropSlot { \
public: \
	PropSlot_##name(const char* name_ = strName); \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override {} \
}; \
PropSlot_##name::PropSlot_##name(const char* name_) : \
	PropSlot(name_, Flag::OfInstance | Flag::Readable)

#define Gurax_DeclareModuleProperty_R(name) Gurax_DeclareModulePropertyAlias_R(name, #name)

#define Gurax_DeclareModulePropertyAlias_RW(name, strName)	\
class PropSlot_##name : public PropSlot { \
public: \
	PropSlot_##name(const char* name_ = strName); \
protected: \
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const override; \
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const override; \
}; \
PropSlot_##name::PropSlot_##name(const char* name_) : \
	PropSlot(name_, Flag::OfInstance | Flag::Readable | Flag::Writable)

#define Gurax_DeclareModuleProperty_RW(name) Gurax_DeclareModulePropertyAlias_RW(name, #name)

#define Gurax_ImplementModulePropertyGetter(name) \
Value* PropSlot_##name::DoGetValue(Value& valueTarget, const Attribute& attr) const

#define Gurax_ImplementModulePropertySetter(name) \
void PropSlot_##name::DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const

#define Gurax_CreateModuleProperty(name) (new PropSlot_##name())

namespace Gurax {

//------------------------------------------------------------------------------
// PropSlot
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PropSlot : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PropSlot);
public:
	// Algorithm operators
	struct GURAX_DLLDECLARE EqualTo_SeqId {
		size_t operator()(const PropSlot* pPropSlot1, const PropSlot* pPropSlot2) const {
			return pPropSlot1->GetSeqId() == pPropSlot2->GetSeqId();
		}
	};
	struct GURAX_DLLDECLARE LessThan_SeqId {
		size_t operator()(const PropSlot* pPropSlot1, const PropSlot* pPropSlot2) const {
			return pPropSlot1->GetSeqId() < pPropSlot2->GetSeqId();
		}
	};
	struct GURAX_DLLDECLARE GreaterThan_SeqId {
		size_t operator()(const PropSlot* pPropSlot1, const PropSlot* pPropSlot2) const {
			return pPropSlot1->GetSeqId() > pPropSlot2->GetSeqId();
		}
	};
	struct GURAX_DLLDECLARE EqualTo_SymbolName {
		size_t operator()(const PropSlot* pPropSlot1, const PropSlot* pPropSlot2) const {
			return Symbol::EqualTo_Name()(pPropSlot1->GetSymbol(), pPropSlot2->GetSymbol());
		}
	};
	struct GURAX_DLLDECLARE LessThan_SymbolName {
		size_t operator()(const PropSlot* pPropSlot1, const PropSlot* pPropSlot2) const {
			return Symbol::LessThan_Name()(pPropSlot1->GetSymbol(), pPropSlot2->GetSymbol());
		}
	};
	struct GURAX_DLLDECLARE GreaterThan_SymbolName {
		size_t operator()(const PropSlot* pPropSlot1, const PropSlot* pPropSlot2) const {
			return Symbol::GreaterThan_Name()(pPropSlot1->GetSymbol(), pPropSlot2->GetSymbol());
		}
	};
public:
	using SeqId = UInt32;
	using Flags = DeclArg::Flags;
	using Flag = DeclArg::Flag;
	using SymbolAssoc_Flag = DeclArg::SymbolAssoc_Flag;
	struct GURAX_DLLDECLARE AttributeOpt {
		SymbolList symbolList;
		SymbolSet symbolSet;
	};
private:
	SeqId _seqId;
	const Symbol* _pSymbol;
	VType* _pVType;
	Flags _flags;
	std::unique_ptr<AttributeOpt> _pAttributeOpt;
	RefPtr<HelpHolder> _pHelpHolder;
public:
	// Constructor
	PropSlot(const Symbol* pSymbol, Flags flags = Flag::None);
	PropSlot(const char* name, Flags flags = Flag::None) : PropSlot(Symbol::Add(name), flags) {}
	// Copy constructor/operator
	PropSlot(const PropSlot& src) = delete;
	PropSlot& operator=(const PropSlot& src) = delete;
	// Move constructor/operator
	PropSlot(PropSlot&& src) = delete;
	PropSlot& operator=(PropSlot&& src) noexcept = delete;
protected:
	// Destructor
	virtual ~PropSlot() = default;
public:
	void SetSeqId(SeqId seqId) { _seqId = seqId; }
	SeqId GetSeqId() const { return _seqId; }
	void Declare(VType& vtype, Flags flags) { _pVType = &vtype, _flags |= flags; }
	void DeclareAttrOpt(const Symbol* pSymbol);
	bool IsSetOpt(const Symbol* pSymbol) const {
		return _pAttributeOpt && _pAttributeOpt->symbolSet.IsSet(pSymbol);
	}
	bool CheckValidAttribute(const Attribute& attr) const;
	HelpHolder& GetHelpHolder() { return *_pHelpHolder; }
	const HelpHolder& GetHelpHolder() const { return *_pHelpHolder; }
	void AddHelp(const Symbol* pLangCode, const char* doc) { _pHelpHolder->AddHelp(pLangCode, doc); }
	void AddHelpTmpl(const Symbol* pLangCode, const char* doc) { _pHelpHolder->AddHelpTmpl(pLangCode, doc); }
	const Symbol* GetSymbol() const { return _pSymbol; }
	VType& GetVType() const { return *_pVType; }
	const Flags GetFlags() const { return _flags; }
	bool IsSet(Flags flags) const { return (GetFlags() & flags) != 0; }
	Value* GetValue(Value& valueTarget, const Attribute& attr) const {
		return DoGetValue(valueTarget, attr);
	}
	bool SetValue(Value& valueTarget, const Value& value, const Attribute& attr) const;
	static Flags SymbolToFlag(const Symbol* pSymbol) {
		return SymbolAssoc_Flag::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* FlagToSymbol(Flags flag) {
		return SymbolAssoc_Flag::GetInstance().ToSymbol(flag);
	}
protected:
	// Virtual functions
	virtual Value* DoGetValue(Value& valueTarget, const Attribute& attr) const = 0;
	virtual void DoSetValue(Value& valueTarget, const Value& value, const Attribute& attr) const = 0;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const PropSlot& PropSlot) const { return this == &PropSlot; }
	bool IsEqualTo(const PropSlot& PropSlot) const { return IsIdentical(PropSlot); }
	bool IsLessThan(const PropSlot& PropSlot) const { return this < &PropSlot; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// PropSlotList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PropSlotList : public ListBase<PropSlot*> {
public:
	PropSlotList& SortBySeqId(SortOrder sortOrder = SortOrder::Ascend);
	PropSlotList& SortBySymbolName(SortOrder sortOrder = SortOrder::Ascend);
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const PropSlotList& PropSlotList) const { return this == &PropSlotList; }
	bool IsEqualTo(const PropSlotList& PropSlotList) const { return IsIdentical(PropSlotList); }
	bool IsLessThan(const PropSlotList& PropSlotList) const { return this < &PropSlotList; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// PropSlotOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PropSlotOwner : public PropSlotList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PropSlotOwner);
protected:
	~PropSlotOwner() { Clear(); }
public:
	void Clear();
};

//------------------------------------------------------------------------------
// PropSlotMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PropSlotMap :
	public std::unordered_map<const Symbol*, PropSlot*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(PropSlotMap);
protected:
	~PropSlotMap() { Clear(); }
public:
	void Clear();
	void Assign(PropSlot* pPropSlot);
	PropSlot* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	PropSlotOwner* CreatePropSlotOwner() const;
	void GatherSymbol(SymbolList& symbolList) const;
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
