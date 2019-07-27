//==============================================================================
// Palette.h
//==============================================================================
#ifndef GURAX_PALETTE_H
#define GURAX_PALETTE_H

namespace Gurax {

//------------------------------------------------------------------------------
// Palette
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Palette : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Palette);
public:
	// Constructor
	Palette() {}
	// Copy constructor/operator
	Palette(const Palette& src) = delete;
	Palette& operator=(const Palette& src) = delete;
	// Move constructor/operator
	Palette(Palette&& src) = delete;
	Palette& operator=(Palette&& src) noexcept = delete;
protected:
	~Palette() = default;
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
