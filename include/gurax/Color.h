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
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Color");
public:
	struct Elem {
		UInt8 b, g, r, a;
		constexpr Elem() : b(0), g(0), r(0), a(0) {}
		constexpr Elem(const Elem& elem) : b(elem.b), g(elem.g), r(elem.r), a(elem.a) {}
		constexpr Elem(UInt8 r, UInt8 g, UInt8 b, UInt8 a) : b(b), g(g), r(r), a(a) {}
	};
	struct NamedEntry {
		const char* name;
		UInt32 packed;
	};
	class GURAX_DLLDECLARE StringMap : public std::unordered_map<String, Color, String::Hash, String::EqualTo> {
	public:
		const Color* Lookup(const char* str) const;
	};
	class GURAX_DLLDECLARE SymbolMap :
		 public std::unordered_map<const Symbol*, Color, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId> {
	public:
		const Color* Lookup(const Symbol* pSymbol) const;
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
protected:
	static const NamedEntry _namedEntries[];
	static StringMap _stringMap;
	static SymbolMap _symbolMap;
public:
	// Constructor
	Color() : _packed(0) {}
	explicit constexpr Color(Elem elem) : _elem(elem) {}
	explicit constexpr Color(UInt32 packed) : _packed(packed) {}
	constexpr Color(UInt8 r, UInt8 g, UInt8 b) : _elem(r, g, b, 0xff) {}
	constexpr Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a) : _elem(r, g, b, a) {}
	// Copy constructor/operator
	Color(const Color& src) : _packed(src._packed) {}
	Color& operator=(const Color& src) { _packed = src._packed; return *this; }
	// Move constructor/operator
	Color(Color&& src) noexcept : _packed(src._packed) {}
	Color& operator=(Color&& src) noexcept { _packed = src._packed; return *this; }
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
	Color GrayScale() const { return GrayScale(*this); }
	static Color GrayScale(const Color& color) {
		return GrayScale(color.GetR(), color.GetG(), color.GetB(), color.GetA());
	}
	static Color GrayScale(UInt8 r, UInt8 g, UInt8 b, UInt8 a) {
		UInt8 gray = CalcGray(r, g, b);
		return Color(gray, gray, gray, a);
	}
	static UInt8 CalcGray(UInt8 r, UInt8 g, UInt8 b) {
		return static_cast<UInt8>(
			(static_cast<UInt32>(r) * 299 + static_cast<UInt32>(g) * 587 +
			 static_cast<UInt32>(b) * 114) / 1000);
	}
public:
	static const Color* Lookup(const char* name) { return _stringMap.Lookup(name); }
	static const Color* Lookup(const Symbol* pSymbol) { return _symbolMap.Lookup(pSymbol); }
public:
	static constexpr UInt32 PackRGB(UInt8 r, UInt8 g, UInt8 b) {
		return (static_cast<UInt32>(r) << 16) + (static_cast<UInt32>(g) << 8) + (static_cast<UInt32>(b) << 0);
	}
	static constexpr UInt32 PackRGBA(UInt8 r, UInt8 g, UInt8 b, UInt8 a) {
		return (static_cast<UInt32>(a) << 24) + (static_cast<UInt32>(r) << 16) +
			(static_cast<UInt32>(g) << 8) + (static_cast<UInt32>(b) << 0);
	}
public:
	int CalcDistSqu(UInt8 r, UInt8 g, UInt8 b) const { return CalcDistSqu(GetR(), GetG(), GetB(), r, g, b); }
	int CalcDistSqu(const Color& color) const { return CalcDistSqu(color.GetR(), color.GetG(), color.GetB()); }
	int CalcDistSqu(UInt32 packed) const { return CalcDistSqu(Color(packed)); }
	static int CalcDistSqu(UInt8 r1, UInt8 g1, UInt8 b1, UInt8 r2, UInt8 g2, UInt8 b2) {
		int distR = static_cast<int>(r1) - static_cast<int>(r2);
		int distG = static_cast<int>(g1) - static_cast<int>(g2);
		int distB = static_cast<int>(b1) - static_cast<int>(b2);
		return distR * distR + distG * distG + distB * distB;
	}
	static int CalcDistSqu(const Color& color1, const Color& color2) { return color1.CalcDistSqu(color2); }
	static int CalcDistSqu(UInt32 packed1, UInt32 packed2) { return Color(packed1).CalcDistSqu(packed2); }
public:
	String MakeHTML() const { return MakeHTML(GetR(), GetG(), GetB()); }
	static String MakeHTML(UInt8 r, UInt8 g, UInt8 b) { return String().Printf("#%02x%02x%02x", r, g, b); }
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
