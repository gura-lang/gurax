//==============================================================================
// VType.h
//==============================================================================
#ifndef GURAX_KLASS_H
#define GURAX_KLASS_H
#include "Help.h"
#include "MemoryPool.h"
#include "Referable.h"
#include "DottedSymbol.h"
#include "Frame.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType
//------------------------------------------------------------------------------
class VType {
public:
	struct Flag {
		static const UInt32 None		= 0;
		static const UInt32 Mutable		= (1 << 0);
		static const UInt32 Immutable	= (0 << 0);
	};
	using SeqId = UInt32;
protected:
	SeqId _seqId;
	RefPtr<HelpProvider> _pHelpProvider;
	VType* _pVTypeInherited;
	const Symbol* _pSymbol;
	UInt32 _flags;
	RefPtr<Frame_Branch> _pFrame;
	RefPtr<Frame::WeakPtr> _pwFrameParent;
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
	void SetAttrs(VType& vtypeInherited, UInt32 flags);
	const HelpProvider& GetHelpProvider() const { return *_pHelpProvider; }
	VType& GetVTypeInherited() const { return *_pVTypeInherited; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const char* GetName() const { return _pSymbol->GetName(); }
	void SetFrameParent(Frame* pFrameParent) { _pwFrameParent.reset(pFrameParent->GetWeakPtr()); }
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
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(vtype)"; }
public:
	void Prepare(Frame* pFrameParent) { DoPrepare(pFrameParent); }
public:
	bool IsMutable() const { return (_flags & Flag::Mutable) != 0; }
	bool IsImmutable() const { return (_flags & Flag::Mutable) == 0; }
public:
	// Virtual functions
	virtual void DoPrepare(Frame* pFrame) {};
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
