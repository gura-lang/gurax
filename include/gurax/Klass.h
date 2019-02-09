//==============================================================================
// Klass.h
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
// Klass
//------------------------------------------------------------------------------
class Klass {
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
	Klass* _pKlassInherited;
	const Symbol* _pSymbol;
	UInt32 _flags;
	RefPtr<Frame_Branch> _pFrame;
	RefPtr<Frame::WeakPtr> _pwFrameParent;
private:
	static SeqId _seqIdNext;
	static const SeqId SeqId_Invalid = 0;
public:
	static Klass Empty;
public:
	// Constructor
	explicit Klass(const char* name);
	// Copy constructor/operator
	Klass(Klass& src) = delete;
	Klass& operator=(Klass& src) = delete;
	// Move constructor/operator
	Klass(Klass&& src) = delete;
	Klass& operator=(Klass&& src) noexcept = delete;
	// Destructor
	virtual ~Klass() = default;
public:
	SeqId GetSeqId() const { return _seqId; }
	void SetAttrs(Klass& klassInherited, UInt32 flags);
	const HelpProvider& GetHelpProvider() const { return *_pHelpProvider; }
	Klass& GetKlassInherited() const { return *_pKlassInherited; }
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
	bool IsIdentical(const Klass& klass) const { return this == &klass; }
	bool IsEqualTo(const Klass& klass) const { return IsIdentical(klass); }
	bool IsLessThan(const Klass& klass) const { return this < &klass; }
	Frame& GetFrame() { return *_pFrame; }
	const Frame& GetFrame() const { return *_pFrame; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const { return "(klass)"; }
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
// KlassMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE KlassMap :
	public std::unordered_map<const Symbol*, Klass*,
			Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(KlassMap);
protected:
	~KlassMap() = default;
public:
	void Assign(const Symbol* pSymbol, Klass* pKlass);
	Klass* Lookup(const Symbol* pSymbol) const {
		auto pPair = find(pSymbol);
		return (pPair == end())? nullptr : pPair->second;
	}
	bool DoesExist(const Symbol* pSymbol) const { return find(pSymbol) != end(); }
	SymbolList GetKeys() const { return SymbolList::CollectKeys(*this); }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
