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
	struct Flag {
		static const UInt32 None			= 0;
	};
	class Occur {
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
	class SymbolAssoc_Flag : public SymbolAssoc<UInt32, 0> {
	public:
		SymbolAssoc_Flag() {
		}
		static SymbolAssoc* GetInstance() {
			return _pInstance? _pInstance : (_pInstance = new SymbolAssoc_Flag());
		}
	};
private:
	const Symbol* _pSymbol;
	const Occur& _occur;
	UInt32 _flags;
public:
	// Constructor
	DeclBlock(const Symbol* pSymbol, const Occur& occur, UInt32 flags);
	// Copy constructor/operator
	DeclBlock(const DeclBlock& src) = delete;
	DeclBlock& operator=(const DeclBlock& src) = delete;
	// Move constructor/operator
	DeclBlock(DeclBlock&& src) = delete;
	DeclBlock& operator=(DeclBlock&& src) noexcept = delete;
protected:
	// Destructor
	~DeclBlock() = default;
public:
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Occur& GetOccur() const { return _occur; }
	bool IsOccurZero() const { return _occur.IsIdentical(Occur::Zero); }
	bool IsOccurOnce() const { return _occur.IsIdentical(Occur::Once); }
	bool IsOccurZeroOrOnce() const { return _occur.IsIdentical(Occur::ZeroOrOnce); }
	UInt32 GetFlags() const { return _flags; }
	static UInt32 SymbolToFlag(const Symbol* pSymbol) {
		return SymbolAssoc_Flag::GetInstance()->ToAssociated(pSymbol);
	}
	static const Symbol* FlagToSymbol(UInt32 flag) {
		return SymbolAssoc_Flag::GetInstance()->ToSymbol(flag);
	}
	static String FlagsToString(UInt32 flags);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const DeclBlock& declBlock) const { return this == &declBlock; }
	bool IsEqualTo(const DeclBlock& declBlock) const { return IsIdentical(declBlock); }
	bool IsLessThan(const DeclBlock& declBlock) const { return this < &declBlock; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
