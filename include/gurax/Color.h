//==============================================================================
// Color.h
//==============================================================================
#ifndef GURAX_COLOR_H
#define GURAX_COLOR_H
#include "String.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Color
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Color {
public:
	struct Elem {
		UInt8 b, g, r, a;
		Elem(UInt8 r, UInt8 g, UInt8 b, UInt8 a) : b(b), g(g), r(r), a(a) {}
	};
private:
	union {
		UInt32 _packed;
		Elem _elem;
	};
public:
	static const Color zero;
	static const Color black;
	static const Color maroon;
	static const Color green;
	static const Color olive;
	static const Color navy;
	static const Color purple;
	static const Color teal;
	static const Color gray;
	static const Color silver;
	static const Color red;
	static const Color lime;
	static const Color yellow;
	static const Color blue;
	static const Color fuchsia;
	static const Color aqua;
	static const Color white;
public:
	// Constructor
	Color() : _packed(0) {}
	explicit Color(UInt32 packed) : _packed(packed) {}
	Color(UInt8 r, UInt8 g, UInt8 b) : _elem(r, g, b, 0xff) {}
	Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a) : _elem(r, g, b, a) {}
	// Copy constructor/operator
	Color(const Color& src) : _packed(src._packed) {}
	Color& operator=(const Color& src) { _packed = src._packed; }
	// Move constructor/operator
	Color(Color&& src) : _packed(src._packed) {}
	Color& operator=(Color&& src) noexcept { _packed = src._packed; }
	// Destructor
	~Color() = default;
public:
	static void Bootup();
public:
	UInt32 GetPacked() const { return _packed; }
	void SetPacked(UInt32 packed) { _packed = packed; }
	UInt8 GetR() const { return _elem.r; }
	UInt8 GetG() const { return _elem.g; }
	UInt8 GetB() const { return _elem.b; }
	UInt8 GetA() const { return _elem.a; }
	void SetR(UInt8 r) { _elem.r = r; }
	void SetG(UInt8 g) { _elem.g = g; }
	void SetB(UInt8 b) { _elem.b = b; }
	void SetA(UInt8 a) { _elem.a = a; }
	UInt32 GetARGB() const {
		return
			(static_cast<UInt32>(GetA()) << 24) + (static_cast<UInt32>(GetR()) << 16) +
			(static_cast<UInt32>(GetG()) << 8) + (static_cast<UInt32>(GetB()) << 0);
	}
	UInt32 GetABGR() const {
		return
			(static_cast<UInt32>(GetA()) << 24) + (static_cast<UInt32>(GetB()) << 16) +
			(static_cast<UInt32>(GetG()) << 8) + (static_cast<UInt32>(GetR()) << 0);
	}
	UInt32 GetRGB() const {
		return
			(static_cast<UInt32>(GetR()) << 16) + (static_cast<UInt32>(GetG()) << 8) +
			(static_cast<UInt32>(GetB()) << 0);
	}
	UInt32 GetBGR() const {
		return
			(static_cast<UInt32>(GetB()) << 16) + (static_cast<UInt32>(GetG()) << 8) +
			(static_cast<UInt32>(GetR()) << 0);
	}
	UInt8 GetGray() const { return CalcGray(GetR(), GetG(), GetB()); }
	static UInt8 CalcGray(UInt8 r, UInt8 g, UInt8 b) {
		return static_cast<UInt8>(
			(static_cast<UInt32>(r) * 299 + static_cast<UInt32>(g) * 587 +
			 static_cast<UInt32>(b) * 114) / 1000);
	}
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Color& color) const { return this == &color; }
	bool IsEqualTo(const Color& color) const { return IsIdentical(color); }
	bool IsLessThan(const Color& color) const { return this < &color; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

#if 0
//------------------------------------------------------------------------------
// NamedColorMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE NamedColorMap : public std::unordered_map<String, Color, String::Hash, String::EqualTo> {
public:
	struct Entry {
		const char* name;
		UChar r, g, b;
	};
private:
	static const Entry _entryTbl[];
public:
	NamedColorMap Inst;
public:
	void Initialize();
	const Color* Lookup(const char* naem);
};
#endif

}

#endif
