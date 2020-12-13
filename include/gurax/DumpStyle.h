//==============================================================================
// DumpStyle.h
//==============================================================================
#ifndef GURAX_DUMPSTYLE_H
#define GURAX_DUMPSTYLE_H
#include "Common.h"

namespace Gurax {

//------------------------------------------------------------------------------
// DumpStyle
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE DumpStyle {
public:
	using Flags = UInt32;
	struct Flag {
		static const Flags None			= 0;
		static const Flags UpperCase	= (1 << 0);
		static const Flags AddrInfo		= (1 << 1);
	};
private:
	Flags _flags;
	size_t _addrOffset;
	size_t _addrUnitSize;
public:
	static const DumpStyle Empty;
public:
	explicit DumpStyle(Flags flags = Flag::None, size_t addrOffset = 0, size_t addrUnitSize = 4) :
				_flags(flags), _addrOffset(addrOffset), _addrUnitSize(addrUnitSize) {}
public:
	DumpStyle& SetUpperCase()	{ _flags |= Flag::UpperCase; return *this; }
	DumpStyle& UnsetUpperCase()	{ _flags &= ~Flag::UpperCase; return *this; }
	DumpStyle& SetAddrInfo()	{ _flags |= Flag::AddrInfo; return *this; }
	DumpStyle& UnsetAddrInfo()	{ _flags &= ~Flag::AddrInfo; return *this; }
	DumpStyle& SetAddrOffset(size_t addrOffset) { _addrOffset = addrOffset; return *this; }
	DumpStyle& SetAddrUnitSize(size_t addrUnitSize) { _addrUnitSize = addrUnitSize; return *this; }
	bool IsUpperCase() const	{ return (_flags & Flag::UpperCase) != 0; }
	bool IsAddrInfo() const		{ return (_flags & Flag::AddrInfo) != 0; }
	size_t GetAddrOffset() const { return _addrOffset; }
	size_t GetAddrUnitSize() const { return _addrUnitSize; }
public:
	static void DeclareAttrOpt(Function& func);
	static Flags ToFlags(const Argument& argument);
};

}

#endif
