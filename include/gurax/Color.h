//==============================================================================
// Color.h
//==============================================================================
#ifndef GURAX_COLOR_H
#define GURAX_COLOR_H

namespace Gurax {

//------------------------------------------------------------------------------
// Color
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Color : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Color);
public:
	// Constructor
	Color() {}
	// Copy constructor/operator
	Color(const Color& src) = delete;
	Color& operator=(const Color& src) = delete;
	// Move constructor/operator
	Color(Color&& src) = delete;
	Color& operator=(Color&& src) noexcept = delete;
protected:
	~Color() = default;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Color& color) const { return this == &color; }
	bool IsEqualTo(const Color& color) const { return IsIdentical(color); }
	bool IsLessThan(const Color& color) const { return this < &color; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ColorList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ColorList : public std::vector<Color*> {
public:
	using std::vector<Color*>::vector;
};

//------------------------------------------------------------------------------
// ColorOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ColorOwner : public ColorList {
public:
	~ColorOwner() { Clear(); }
	void Clear();
};

}

#endif
