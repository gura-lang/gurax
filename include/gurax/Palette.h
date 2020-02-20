//==============================================================================
// Palette.h
//==============================================================================
#ifndef GURAX_PALETTE_H
#define GURAX_PALETTE_H
#include "Referable.h"
#include "Color.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Palette
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Palette : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Palette);
protected:
	std::unique_ptr<UInt32[]> _entryTbl;
public:
	static void Bootup();
public:
	// Constructor
	Palette(size_t n);
	Palette(const UInt32* entryTbl, size_t n);
	// Copy constructor/operator
	Palette(const Palette& src) = delete;
	Palette& operator=(const Palette& src) = delete;
	// Move constructor/operator
	Palette(Palette&& src) = delete;
	Palette& operator=(Palette&& src) noexcept = delete;
protected:
	~Palette() = default;
public:
	static Palette* Basic();
	static Palette* WebSafe();
	static Palette* Win256();
	static constexpr UInt32 Entry(UInt8 r, UInt8 g, UInt8 b, UInt8 a) {
		return (static_cast<UInt32>(a) << 24) + (static_cast<UInt32>(r) << 16) +
			(static_cast<UInt32>(g) << 8) + (static_cast<UInt32>(b) << 0);
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Palette& palette) const { return this == &palette; }
	bool IsEqualTo(const Palette& palette) const { return IsIdentical(palette); }
	bool IsLessThan(const Palette& palette) const { return this < &palette; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// PaletteList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PaletteList : public std::vector<Palette*> {
public:
	using std::vector<Palette*>::vector;
};

//------------------------------------------------------------------------------
// PaletteOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE PaletteOwner : public PaletteList {
public:
	~PaletteOwner() { Clear(); }
	void Clear();
};

}

#endif
