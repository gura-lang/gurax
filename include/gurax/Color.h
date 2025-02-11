﻿//==============================================================================
// Color.h
//==============================================================================
#ifndef GURAX_COLOR_H
#define GURAX_COLOR_H
#include "String.h"
#include "StringStyle.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Color
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Color {
public:
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Color");
public:
	// Algorithm operators
	struct EqualTo {
		bool operator()(const Color& color1, const Color& color2) const {
			return color1.IsEqualTo(color2);
		}
	};
	struct LessThan {
		bool operator()(const Color& color1, const Color& color2) const {
			return color1.IsLessThan(color2);
		}
	};
	struct GreaterThan {
		bool operator()(const Color& color1, const Color& color2) const {
			return color2.IsLessThan(color1);
		}
	};
	struct Hash {
		size_t operator()(const Color& color) const {
			return color.CalcHash();
		}
	};
public:
	using PackedType = UInt32;
	struct Elem {
		UInt8 b, g, r, a;
		constexpr Elem() : b(0), g(0), r(0), a(0) {}
		constexpr Elem(const Elem& elem) : b(elem.b), g(elem.g), r(elem.r), a(elem.a) {}
		constexpr Elem(UInt8 r, UInt8 g, UInt8 b, UInt8 a) : b(b), g(g), r(r), a(a) {}
	};
	struct NamedEntry {
		const char* name;
		PackedType packed;
	};
private:
	union {
		PackedType _packed;
		Elem _elem;
	};
public:
	static const Color zero;
	static const Color black;
	static const Color silver;
	static const Color gray;
	static const Color white;
	static const Color maroon;
	static const Color red;
	static const Color purple;
	static const Color fuchsia;
	static const Color green;
	static const Color lime;
	static const Color olive;
	static const Color yellow;
	static const Color navy;
	static const Color blue;
	static const Color teal;
	static const Color aqua;
protected:
	static const NamedEntry _namedEntries[];
public:
	// Constructor
	constexpr Color() : _packed(0) {}
	explicit constexpr Color(Elem elem) : _elem(elem) {}
	explicit constexpr Color(PackedType packed) : _packed(packed) {}
	constexpr Color(UInt8 r, UInt8 g, UInt8 b) : _elem(r, g, b, 0xff) {}
	constexpr Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a) : _elem(r, g, b, a) {}
	Color(PackedType packed, UInt8 a) : _packed(packed) { SetA(a); }
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
	static bool FromString(Color& color, const char* str, UInt8 alpha);
public:
	constexpr PackedType GetPacked() const { return _packed; }
	void SetPacked(PackedType packed) { _packed = packed; }
	UInt8 GetR() const { return _elem.r; }
	UInt8 GetG() const { return _elem.g; }
	UInt8 GetB() const { return _elem.b; }
	UInt8 GetA() const { return _elem.a; }
	void SetR(UInt8 r) { _elem.r = r; }
	void SetG(UInt8 g) { _elem.g = g; }
	void SetB(UInt8 b) { _elem.b = b; }
	void SetA(UInt8 a) { _elem.a = a; }
	void SetRGB(UInt8 r, UInt8 g, UInt8 b) { _elem.r = r, _elem.g = g, _elem.b = b; }
	void SetRGBA(UInt8 r, UInt8 g, UInt8 b, UInt8 a) { _elem.r = r, _elem.g = g, _elem.b = b, _elem.a = a; }
	void SetRGB565(UInt16 rgb565) {
		_elem.b = static_cast<UInt8>(rgb565 & 0x1f) << 3; rgb565 >>= 5;
		_elem.g = static_cast<UInt8>(rgb565 & 0x3f) << 2; rgb565 >>= 6;
		_elem.r = static_cast<UInt8>(rgb565) << 3;
		if (_elem.b) _elem.b |= 0x07;
		if (_elem.g) _elem.g |= 0x03;
		if (_elem.r) _elem.r |= 0x07;
	}
	void SetRGB555(UInt16 rgb555) {
		_elem.b = static_cast<UInt8>(rgb555 & 0x1f) << 3; rgb555 >>= 5;
		_elem.g = static_cast<UInt8>(rgb555 & 0x1f) << 3; rgb555 >>= 5;
		_elem.r = static_cast<UInt8>(rgb555) << 3;
		if (_elem.b) _elem.b |= 0x07;
		if (_elem.g) _elem.g |= 0x07;
		if (_elem.r) _elem.r |= 0x07;
	}
	UInt16 GetRGB565() const { return
		(static_cast<UInt16>(_elem.r & 0xf8) << (6 + 5 - 3)) |
		(static_cast<UInt16>(_elem.g & 0xfc) << (5 - 2)) |
		(static_cast<UInt16>(_elem.b) >> 3);
	}
	UInt16 GetRGB555() const { return
		(static_cast<UInt16>(_elem.r & 0xf8) << (5 + 5 - 3)) |
		(static_cast<UInt16>(_elem.g & 0xf8) << (5 - 3)) |
		(static_cast<UInt16>(_elem.b) >> 3);
	}
	Color GrayScale() const { return GrayScale(*this); }
	static Color GrayScale(const Color& color) {
		return GrayScale(color.GetR(), color.GetG(), color.GetB(), color.GetA());
	}
	static Color GrayScale(UInt8 r, UInt8 g, UInt8 b, UInt8 a) {
		UInt8 gray = CalcGray(r, g, b);
		return Color(gray, gray, gray, a);
	}
	UInt8 CalcGray() const { return CalcGray(*this); }
	static UInt8 CalcGray(const Color& color) {
		return CalcGray(color.GetR(), color.GetG(), color.GetB());
	}
	static UInt8 CalcGray(UInt8 r, UInt8 g, UInt8 b) {
		return static_cast<UInt8>(
			(static_cast<PackedType>(r) * 299 + static_cast<PackedType>(g) * 587 +
			 static_cast<PackedType>(b) * 114) / 1000);
	}
public:
	static const Color* Lookup(const char* name);
	static const Color* Lookup(const Symbol* pSymbol);
public:
	static constexpr PackedType PackRGB(UInt8 r, UInt8 g, UInt8 b) { return Color(r, g, b).GetPacked(); }
	static constexpr PackedType PackRGBA(UInt8 r, UInt8 g, UInt8 b, UInt8 a) { return Color(r, g, b, a).GetPacked(); }
public:
	int CalcDistSqu(UInt8 r, UInt8 g, UInt8 b) const { return CalcDistSqu(GetR(), GetG(), GetB(), r, g, b); }
	int CalcDistSqu(const Color& color) const { return CalcDistSqu(color.GetR(), color.GetG(), color.GetB()); }
	int CalcDistSqu(PackedType packed) const { return CalcDistSqu(Color(packed)); }
	static int CalcDistSqu(UInt8 r1, UInt8 g1, UInt8 b1, UInt8 r2, UInt8 g2, UInt8 b2) {
		int distR = static_cast<int>(r1) - static_cast<int>(r2);
		int distG = static_cast<int>(g1) - static_cast<int>(g2);
		int distB = static_cast<int>(b1) - static_cast<int>(b2);
		return distR * distR + distG * distG + distB * distB;
	}
	static int CalcDistSqu(const Color& color1, const Color& color2) { return color1.CalcDistSqu(color2); }
	static int CalcDistSqu(PackedType packed1, PackedType packed2) { return Color(packed1).CalcDistSqu(packed2); }
public:
	String MakeHTML() const { return MakeHTML(GetR(), GetG(), GetB()); }
	static String MakeHTML(UInt8 r, UInt8 g, UInt8 b) { return String().Format("#%02x%02x%02x", r, g, b); }
public:
	size_t CalcHash() const { return _packed; }
	bool IsIdentical(const Color& color) const { return _packed == color._packed; }
	bool IsEqualTo(const Color& color) const { return _packed == color._packed; }
	bool IsLessThan(const Color& color) const { return _packed < color._packed; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// ColorStringMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ColorStringMap {
public:
	using Map = std::unordered_map<String, Color, String::Hash, String::EqualTo>;
private:
	Map _map;
public:
	static ColorStringMap Instance;
public:
	Map& GetMap() { return _map; }
	const Map& GetMap() const { return _map; }
	const Color* Lookup(const char* str) const;
};

//------------------------------------------------------------------------------
// ColorSymbolMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE ColorSymbolMap {
public:
	using Map = std::unordered_map<const Symbol*, Color, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId>;
private:
	Map _map;
public:
	static ColorSymbolMap Instance;
public:
	Map& GetMap() { return _map; }
	const Map& GetMap() const { return _map; }
	const Color* Lookup(const Symbol* pSymbol) const;
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
