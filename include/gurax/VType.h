//==============================================================================
// VType.h
//==============================================================================
#ifndef GURAX_VTYPE_H
#define GURAX_VTYPE_H
#include "Help.h"
#include "MemoryPool.h"
#include "Referable.h"
#include "DottedSymbol.h"
#include "Frame.h"
#include "PropSlot.h"
#include "DeclArg.h"

namespace Gurax {

class Argument;
class DeclCallable;
class Processor;
class Constructor;
class OpEntry;

//------------------------------------------------------------------------------
// VType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType {
public:
	using UniqId = UInt32;
	using SerialId = UInt32;
	using Flags = UInt32;
	struct Flag {
		static const Flags None			= 0;
		static const Flags Mutable		= (1 << 0);
		static const Flags Immutable	= (0 << 0);
		static const Flags Callable		= (1 << 1);
	};
	using OpEntryList = ListBase<OpEntry*>;
	using SerialIdMap = std::unordered_map<SerialId, VType*>;
protected:
	UniqId _uniqId;
	SerialId _serialId;
	RefPtr<HelpHolder> _pHelpHolder;
	VType* _pVTypeInh;
	const Symbol* _pSymbol;
	Flags _flags;
	RefPtr<Frame_Scope> _pFrame;
	RefPtr<Constructor> _pConstructor;
	OpEntryList _opEntryList;
private:
	static UniqId _uniqIdNext;
	static SerialIdMap _serialIdMap;
	static const UniqId UniqId_Invalid = 0;
	static const SerialId SerialId_Invalid = 0;
public:
	static VType Invalid;
public:
	// Constructor
	VType(SerialId serialId = SerialId_Invalid);
	explicit VType(const Symbol* pSymbol, SerialId serialId = SerialId_Invalid);
	explicit VType(const char* name, SerialId serialId = SerialId_Invalid) : VType(Symbol::Add(name), serialId) {}
	// Copy constructor/operator
	VType(VType& src) = delete;
	VType& operator=(VType& src) = delete;
	// Move constructor/operator
	VType(VType&& src) = delete;
	VType& operator=(VType&& src) noexcept = delete;
	// Destructor
	virtual ~VType() = default;
public:
	bool IsValid() const { return _uniqId != UniqId_Invalid; }
	bool IsInvalid() const { return _uniqId == UniqId_Invalid; }
	UniqId GetUniqId() const { return _uniqId; }
	SerialId GetSerialId() const { return _serialId; }
	bool IsSerializable() const { return _serialId != SerialId_Invalid; }
	void Declare(VType& vtypeInh, Flags flags, Constructor* pConstructor = nullptr);
	HelpHolder& GetHelpHolder() { return *_pHelpHolder; }
	const HelpHolder& GetHelpHolder() const { return *_pHelpHolder; }
	VType& GetVTypeInh() const { return *_pVTypeInh; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const char* GetName() const { return _pSymbol->GetName(); }
	String MakeFullName() const;
	DottedSymbol* MakeDottedSymbol() const;
	void AddHelp(const Symbol* pLangCode, const char* doc) { _pHelpHolder->AddHelp(pLangCode, doc); }
	void AddHelp(const char* langCode, const char* doc) { _pHelpHolder->AddHelp(langCode, doc); }
	void AddOpEntry(OpEntry* pOpEntry) { if (!_opEntryList.DoesExist(pOpEntry)) _opEntryList.push_back(pOpEntry); }
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const VType& vtype) const { return this == &vtype; }
	bool IsEqualTo(const VType& vtype) const { return IsIdentical(vtype); }
	bool IsLessThan(const VType& vtype) const { return this < &vtype; }
	Frame& GetFrame() { return *_pFrame; }
	const Frame& GetFrame() const { return *_pFrame; }
	void SetFrameOuter(Frame* pFrameOuter) { _pFrame->SetFrameOuter(pFrameOuter); }
	Frame* GetFrameOuter() { return _pFrame->GetFrameOuter(); }
	const Frame* GetFrameOuter() const { return _pFrame->GetFrameOuter(); }
	Frame& GetFrameOfMember() { return *_pFrame->GetFrameLocal(); }
	const Frame& GetFrameOfMember() const { return *_pFrame->GetFrameLocal(); }
	ValueMap& GetValueMap() {
		return dynamic_cast<Frame_OfMember*>(_pFrame->GetFrameLocal())->GetValueMap();
	}
	const ValueMap& GetValueMap() const {
		return dynamic_cast<Frame_OfMember*>(_pFrame->GetFrameLocal())->GetValueMap();
	}
	PropSlotMap& GetPropSlotMap() {
		return dynamic_cast<Frame_OfMember*>(_pFrame->GetFrameLocal())->GetPropSlotMap();
	}
	const PropSlotMap& GetPropSlotMap() const {
		return dynamic_cast<Frame_OfMember*>(_pFrame->GetFrameLocal())->GetPropSlotMap();
	}
	const PropSlot* LookupPropSlot(const Symbol* pSymbol) const;
	Constructor& GetConstructor() { return *_pConstructor; }
	const Constructor& GetConstructor() const { return *_pConstructor; }
	Value* Cast(Processor& processor, const Value& value, const Symbol* pSymbol = nullptr, DeclArg::Flags flags = DeclArg::Flag::None) const;
	void Assign(const Symbol* pSymbol, Value* pValue) { GetFrameOfMember().Assign(pSymbol, pValue); }
	void Assign(const char* name, Value* pValue) { GetFrameOfMember().Assign(name, pValue); }
	void Assign(VType& vtype) { GetFrameOfMember().Assign(vtype); }
	void Assign(Function* pFunction);
	void Assign(PropSlot* pPropSlot) { GetPropSlotMap().Assign(pPropSlot); }
	void GatherMemberSymbol(SymbolList& symbolList, bool escalateFlag) const;
	void GatherMemberSymbolIf(SymbolList& symbolList, const Frame::GatherCriteria& gatherCriteria, bool escalateFlag) const;
	void PresentHelp(Processor& processor, const Symbol* pLangCode) const;
public:
	static VType* SerialIdToVType(SerialId serialId);
	virtual Value* DoDeserialize(Stream& stream) const;
public:
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	bool IsMutable() const { return (_flags & Flag::Mutable) != 0; }
	bool IsImmutable() const { return (_flags & Flag::Mutable) == 0; }
public:
	// Virtual functions
	virtual void PrepareForAssignment(Processor& processor, const Symbol* pSymbol) {};
	virtual bool IsAny() const { return false; }
	virtual bool IsCustom() const { return false; }
	virtual bool IsNil() const { return false; }
	virtual bool IsUndefined() const { return false; }
	virtual bool IsList() const { return false; }
	virtual bool IsIterator() const { return false; }
	virtual bool IsListOrIterator() const { return false; }
	virtual void DoPrepare(Frame& frameOuter) {};
	virtual Value* DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const { return nullptr; }
	virtual Value* DoCastTo(Processor& processor, const Value& value, const VType& vtype, DeclArg::Flags flags) const { return nullptr; }
	virtual bool DoAssignCustomMethod(RefPtr<Function> pFunction);
};

//------------------------------------------------------------------------------
// VTypeMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VTypeMap : public Referable {
public:
	using Map = std::unordered_map<const Symbol*, VType*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
private:
	Map _map;
public:
	// Referable declaration
	Gurax_DeclareReferable(VTypeMap);
protected:
	~VTypeMap() = default;
public:
	Map& GetMap() { return _map; }
	const Map& GetMap() const { return _map; }
	void Assign(const Symbol* pSymbol, VType* pVType);
	VType* Lookup(const Symbol* pSymbol) const {
		auto pPair = _map.find(pSymbol);
		return (pPair == _map.end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return _map.find(pSymbol) != _map.end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
