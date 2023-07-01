//==============================================================================
// Palette.h
//==============================================================================
#ifndef GURAX_PALETTE_H
#define GURAX_PALETTE_H
#include "Referable.h"
#include "Color.h"
#include "ListBase.h"

namespace Gurax {

class Image;

//------------------------------------------------------------------------------
// Palette
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Palette : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Palette);
public:
	enum class ShrinkMode { None, Align, Minimum };
	using ColorSet = std::unordered_set<Color, Color::Hash, Color::EqualTo>;
protected:
	std::unique_ptr<Color::PackedType[]> _packedTbl;
	size_t _n;
public:
	static void Bootup();
public:
	// Constructor
	Palette(size_t n);
	Palette(const Color::PackedType* packedTbl, size_t n);
	// Copy constructor/operator
	Palette(const Palette& src) = delete;
	Palette& operator=(const Palette& src) = delete;
	// Move constructor/operator
	Palette(Palette&& src) = delete;
	Palette& operator=(Palette&& src) noexcept = delete;
protected:
	~Palette() = default;
public:
	static Palette* Mono();
	static Palette* Basic();
	static Palette* WebSafe();
	static Palette* Win256();
	static Palette* CreateFromSymbol(const Symbol* pSymbol);
public:
	Palette* Clone() const { return new Palette(_packedTbl.get(), _n); }
	size_t GetSize() const { return _n; }
	void Fill(const Color& color);
	void SetPacked(size_t idx, Color::PackedType packed) { _packedTbl[idx] = packed; }
	void SetColor(size_t idx, const Color& color) { _packedTbl[idx] = color.GetPacked(); }
	void SetRGB(size_t idx, UInt8 r, UInt8 g, UInt8 b) { SetColor(idx, Color(r, g, b)); }
	void SetRGBA(size_t idx, UInt8 r, UInt8 g, UInt8 b, UInt8 a) { SetColor(idx, Color(r, g, b, a)); }
	Color::PackedType GetPacked(size_t idx) const { return _packedTbl[idx]; }
	Color GetColor(size_t idx) const { return Color(_packedTbl[idx]); }
	Color GetColor(size_t idx, UInt8 a) const { return Color(_packedTbl[idx], a); }
public:
	size_t LookupNearest(UInt8 r, UInt8 g, UInt8 b) const;
	size_t LookupNearest(const Color& color) const {
		return LookupNearest(color.GetR(), color.GetG(), color.GetB());
	}
	bool UpdateByImage(const Image& image, ShrinkMode shrinkMode);
	bool UpdateByPalette(const Palette& palette, ShrinkMode shrinkMode);
	void Shrink(size_t nEntries, bool alignFlag);
	void ResizeBuff(size_t nEntries, size_t nEntriesToCopy);
	size_t NextBlankIndex(ColorSet& colorSet) const;
public:
	bool IndexSet(const Value& valueIndex, RefPtr<Value> pValue);
	bool IndexGet(const Value& valueIndex, Value** ppValue) const;
public:
	static constexpr Color::PackedType PackRGB(UInt8 r, UInt8 g, UInt8 b) { return Color::PackRGB(r, g, b); }
	static constexpr Color::PackedType PackRGBA(UInt8 r, UInt8 g, UInt8 b, UInt8 a) { return Color::PackRGBA(r, g, b, a); }
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
class GURAX_DLLDECLARE PaletteList : public ListBase<Palette*> {
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
