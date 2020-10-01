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

//------------------------------------------------------------------------------
// VType
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType {
public:
	using UniqId = UInt32;
	using Flags = UInt32;
	struct Flag {
		static const Flags None			= 0;
		static const Flags Mutable		= (1 << 0);
		static const Flags Immutable	= (0 << 0);
		static const Flags Callable		= (1 << 1);
	};
protected:
	UniqId _uniqId;
	RefPtr<HelpHolder> _pHelpHolder;
	VType* _pVTypeInh;
	const Symbol* _pSymbol;
	Flags _flags;
	RefPtr<Frame_Scope> _pFrame;
	RefPtr<PropSlotMap> _pPropSlotMap;
	RefPtr<Function> _pConstructor;
private:
	static UniqId _uniqIdNext;
	static const UniqId UniqId_Invalid = 0;
public:
	static VType Empty;
public:
	// Constructor
	explicit VType(const Symbol* pSymbol);
	explicit VType(const char* name) : VType(Symbol::Add(name)) {}
	// Copy constructor/operator
	VType(VType& src) = delete;
	VType& operator=(VType& src) = delete;
	// Move constructor/operator
	VType(VType&& src) = delete;
	VType& operator=(VType&& src) noexcept = delete;
	// Destructor
	virtual ~VType() = default;
public:
	UniqId GetUniqId() const { return _uniqId; }
	void Declare(VType& vtypeInh, Flags flags, Function* pConstructor = nullptr);
	HelpHolder& GetHelpHolder() { return *_pHelpHolder; }
	const HelpHolder& GetHelpHolder() const { return *_pHelpHolder; }
	VType* GetVTypeInh() const { return _pVTypeInh; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const char* GetName() const { return _pSymbol->GetName(); }
	String MakeFullName() const;
	DottedSymbol* MakeDottedSymbol() const;
	void AddHelp(const Symbol* pLangCode, const char* doc) { _pHelpHolder->AddHelp(pLangCode, doc); }
	void AddHelpTmpl(const Symbol* pLangCode, const char* doc) { _pHelpHolder->AddHelpTmpl(pLangCode, doc); }
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
	PropSlotMap& GetPropSlotMap() { return *_pPropSlotMap; }
	const PropSlotMap& GetPropSlotMap() const { return *_pPropSlotMap; }
	const PropSlot* LookupPropSlot(const Symbol* pSymbol) const;
	Function& GetConstructor() { return *_pConstructor; }
	const Function& GetConstructor() const { return *_pConstructor; }
	Value* Cast(const Value& value, const Symbol* pSymbol, DeclArg::Flags flags) const;
	void Assign(const Symbol* pSymbol, Value* pValue) { GetFrameOfMember().Assign(pSymbol, pValue); }
	void Assign(const char* name, Value* pValue) { GetFrameOfMember().Assign(name, pValue); }
	void Assign(VType& vtype) { GetFrameOfMember().Assign(vtype); }
	void Assign(Function* pFunction);
	void Assign(PropSlot* pPropSlot) { GetPropSlotMap().Assign(pPropSlot); }
	void GatherMemberSymbol(SymbolList& symbolList) const;
	void PresentHelp(Processor& processor, const Symbol* pLangCode) const;
public:
	void Prepare(Frame& frameOuter);
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	bool IsMutable() const { return (_flags & Flag::Mutable) != 0; }
	bool IsImmutable() const { return (_flags & Flag::Mutable) == 0; }
public:
	// Virtual functions
	virtual void PrepareForAssignment(Processor& processor, const Symbol* pSymbol) {};
	virtual bool IsCustom() const { return false; }
	virtual bool IsNil() const { return false; }
	virtual bool IsUndefined() const { return false; }
	virtual bool IsList() const { return false; }
	virtual bool IsIterator() const { return false; }
	virtual bool IsListOrIterator() const { return false; }
	virtual void DoPrepare(Frame& frameOuter) {};
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const;
	virtual bool DoAssignCustomMethod(RefPtr<Function> pFunction);
};

//------------------------------------------------------------------------------
// VTypeMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VTypeMap :
	public std::unordered_map<const Symbol*, VType*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(VTypeMap);
protected:
	~VTypeMap() = default;
public:
	void Assign(const Symbol* pSymbol, VType* pVType);
	VType* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
