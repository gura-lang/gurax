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
#include "PropHandler.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType
//------------------------------------------------------------------------------
class VType {
public:
	using SeqId = UInt32;
	using Flags = UInt32;
	struct Flag {
		static const Flags None			= 0;
		static const Flags Mutable		= (1 << 0);
		static const Flags Immutable	= (0 << 0);
		static const Flags Callable		= (1 << 1);
	};
protected:
	SeqId _seqId;
	RefPtr<HelpProvider> _pHelpProvider;
	VType* _pVTypeInherited;
	const Symbol* _pSymbol;
	Flags _flags;
	RefPtr<Frame_VType> _pFrame;
	RefPtr<Frame::WeakPtr> _pwFrameParent;		// may be nullptr
	RefPtr<PropHandlerMap> _pPropHandlerMap;
private:
	static SeqId _seqIdNext;
	static const SeqId SeqId_Invalid = 0;
public:
	static VType Empty;
public:
	// Constructor
	explicit VType(const char* name);
	// Copy constructor/operator
	VType(VType& src) = delete;
	VType& operator=(VType& src) = delete;
	// Move constructor/operator
	VType(VType&& src) = delete;
	VType& operator=(VType&& src) noexcept = delete;
	// Destructor
	virtual ~VType() = default;
public:
	SeqId GetSeqId() const { return _seqId; }
	void SetAttrs(VType& vtypeInherited, Flags flags);
	const HelpProvider& GetHelpProvider() const { return *_pHelpProvider; }
	VType* GetVTypeInherited() const { return _pVTypeInherited; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const char* GetName() const { return _pSymbol->GetName(); }
	void SetFrameParent(Frame& frameParent) { _pwFrameParent.reset(frameParent.GetWeakPtr()); }
	Frame* LockFrameParent() { return _pwFrameParent? _pwFrameParent->Lock() : nullptr; }
	String MakeFullName() const;
	DottedSymbol* MakeDottedSymbol() const;
	void AddHelp(const Symbol* pLangCode, String formatName, String doc) {
		_pHelpProvider->AddHelp(pLangCode, std::move(formatName), std::move(doc));
	}
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const VType& vtype) const { return this == &vtype; }
	bool IsEqualTo(const VType& vtype) const { return IsIdentical(vtype); }
	bool IsLessThan(const VType& vtype) const { return this < &vtype; }
	Frame& GetFrame() { return *_pFrame; }
	const Frame& GetFrame() const { return *_pFrame; }
	PropHandlerMap& GetPropHandlerMap() { return *_pPropHandlerMap; }
	const PropHandlerMap& GetPropHandlerMap() const { return *_pPropHandlerMap; }
	void AssignPropHandler(PropHandler* pPropHandler) { GetPropHandlerMap().Assign(pPropHandler); }
	const PropHandler* LookupPropHandler(const Symbol* pSymbol) const;
	Value* DoPropGet(Value* pValueTarget, const Symbol* pSymbol, const Attribute& attr) const;
	void DoPropSet(Value* pValueTarget, const Symbol* pSymbol, Value* pValue, const Attribute& attr) const;
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(vtype)"; }
	Value* Cast(const Value& value) const;
	void Assign(const Symbol* pSymbol, Value* pValue) { GetFrame().Assign(pSymbol, pValue); }
	void Assign(const char* name, Value* pValue) { GetFrame().Assign(name, pValue); }
	void Assign(VType& vtype) { GetFrame().Assign(vtype); }
	void Assign(Function* pFunction) { GetFrame().Assign(pFunction); }
public:
	static void PrepareBasic(Frame& frame);
public:
	void Prepare(Frame& frameParent) { DoPrepare(frameParent); }
public:
	bool IsMutable() const { return (_flags & Flag::Mutable) != 0; }
	bool IsImmutable() const { return (_flags & Flag::Mutable) == 0; }
public:
	// Virtual functions
	virtual void DoPrepare(Frame& frame) {};
	virtual Value* DoCastFrom(const Value& value) const;
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
