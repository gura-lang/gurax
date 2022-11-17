//==============================================================================
// DeclBlock.h
//==============================================================================
#ifndef GURAX_DECLBLOCK_H
#define GURAX_DECLBLOCK_H
#include "Attribute.h"
#include "Symbols.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DeclBlock
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DeclBlock {
public:
	using Flags = UInt32;
	struct GURAX_DLLDECLARE Flag {
		static const Flags None		= 0;
		static const Flags Quote	= (1 << 0);
	};
	class GURAX_DLLDECLARE Occur {
	private:
		const char* _marker;
	public:
		static const Occur Invalid;
		static const Occur Zero;		// (none)
		static const Occur Once;		// 1
		static const Occur ZeroOrOnce;	// ?
	public:
		// Constructor
		explicit Occur(const char* marker) : _marker(marker) {}
		// Copy constructor/operator
		Occur(const Occur& src) = delete;
		Occur& operator=(const Occur& src) = delete;
		// Move constructor/operator
		Occur(Occur&& src) = delete;
		Occur& operator=(Occur&& src) noexcept = delete;
		// Destructor
		virtual ~Occur() = default;
	public:
		const char* GetMarker() const { return _marker; }
	public:
		size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
		bool IsIdentical(const Occur& occur) const { return this == &occur; }
		bool IsEqualTo(const Occur& occur) const { return IsIdentical(occur); }
		bool IsLessThan(const Occur& occur) const { return this < &occur; }
	};
	class GURAX_DLLDECLARE SymbolAssoc_Flag : public SymbolAssoc<Flags, Flag::None> {
	public:
		SymbolAssoc_Flag() {
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_Flag());
		}
	};
private:
	const Symbol* _pSymbol;
	const Occur* _pOccur;
	Flags _flags;
public:
	// Constructor
	DeclBlock();
	// Copy constructor/operator
	DeclBlock(const DeclBlock& src) = delete;
	DeclBlock& operator=(const DeclBlock& src) = delete;
	// Move constructor/operator
	DeclBlock(DeclBlock&& src) = delete;
	DeclBlock& operator=(DeclBlock&& src) noexcept = delete;
	// Destructor
	~DeclBlock() = default;
public:
	DeclBlock& SetSymbol(const Symbol* pSymbol) { _pSymbol = pSymbol; return *this; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	DeclBlock& SetOccur(const Occur& occur) { _pOccur = &occur; return *this; }
	const Occur& GetOccur() const { return *_pOccur; }
	bool IsOccurZero() const { return GetOccur().IsIdentical(Occur::Zero); }
	bool IsOccurOnce() const { return GetOccur().IsIdentical(Occur::Once); }
	bool IsOccurZeroOrOnce() const { return GetOccur().IsIdentical(Occur::ZeroOrOnce); }
	DeclBlock& SetFlags(Flags flags) { _flags = flags; return *this; }
	Flags GetFlags() const { return _flags; }
	bool IsSet(Flags flags) const { return (GetFlags() & flags) != 0; }
	static Flags SymbolToFlag(const Symbol* pSymbol) {
		return SymbolAssoc_Flag::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* FlagToSymbol(Flags flag) {
		return SymbolAssoc_Flag::GetInstance().ToSymbol(flag);
	}
	static String FlagsToString(Flags flags);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DeclBlock& declBlock) const { return this == &declBlock; }
	bool IsEqualTo(const DeclBlock& declBlock) const { return IsIdentical(declBlock); }
	bool IsLessThan(const DeclBlock& declBlock) const { return this < &declBlock; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
