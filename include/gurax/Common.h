//==============================================================================
// Common.h
//==============================================================================
#ifndef GURAX_COMMON_H
#define GURAX_COMMON_H
#if defined(_MSC_VER)
#include <windows.h>
#endif
#include <array>
#include <algorithm>
#include <complex>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <ratio>
#include <regex>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#undef min
#undef max
#undef SetProp
#undef GetProp
#undef GetObject

//------------------------------------------------------------------------------
// Macros to handler platform differences
//------------------------------------------------------------------------------
#if defined(_MSC_VER)
#define GURAX_ON_MSWIN
#define GURAX_PLATFORM_NAME "mswin"
#define GURAX_CXX11_ABI
#define GURAX_HOST_COMPILER_NAME "msc"
#define _CRT_SECURE_NO_WARNINGS
#elif defined(__linux__)
#define GURAX_ON_LINUX
#define GURAX_PLATFORM_NAME "linux"
#define GURAX_CXX11_ABI __attribute__((abi_tag("cxx11")))
#define GURAX_HOST_COMPILER_NAME "gnuc"
#elif defined(__APPLE__)
#define GURAX_ON_DARWIN
#define GURAX_PLATFORM_NAME "darwin"
#define GURAX_CXX11_ABI
#define GURAX_HOST_COMPILER_NAME "gnuc"
#else
#define GURAX_ON_UNKNOWN
#define GURAX_PLATFORM_NAME "unknown"
#define GURAX_CXX11_ABI
#define GURAX_HOST_COMPILER_NAME "unknown"
#endif

#if defined(GURAX_ON_MSWIN)
#pragma warning(disable:4018)
#pragma warning(disable:4146)
#pragma warning(disable:4200)
#pragma warning(disable:4244)
#pragma warning(disable:4251)
#pragma warning(disable:4267)
#pragma warning(disable:4275)
#pragma warning(disable:4355)
#pragma warning(disable:4800)
#pragma warning(disable:4804)
#pragma warning(disable:4805)
#pragma warning(disable:4996)
#pragma warning(disable:6285)
#define GURAX_DLLIMPORT __declspec(dllimport)
#define GURAX_DLLEXPORT __declspec(dllexport)
#if defined(guraxcore_EXPORTS)
#define GURAX_DLLDECLARE __declspec(dllexport)
#else
#define GURAX_DLLDECLARE __declspec(dllimport)
#endif
#define strcasecmp stricmp
#define GURAX_USE_MSWIN_DIB 1
#else
#define GURAX_DLLIMPORT
#define GURAX_DLLEXPORT
#define GURAX_DLLDECLARE
#define GURAX_USE_MSWIN_DIB 0
#endif

//------------------------------------------------------------------------------
// Macros useful for automaton
//------------------------------------------------------------------------------
#define Gurax_BeginPushbackRegion() \
bool gurax_pushbackFlag = false; \
do { \
gurax_pushbackFlag = false

#define Gurax_EndPushbackRegion() \
} while (gurax_pushbackFlag)

#define Gurax_Pushback() \
gurax_pushbackFlag = true

#define Gurax_PushbackCancel() \
gurax_pushbackFlag = false

#define Gurax_BeginPushbackRegionEx(T, n, var)	\
T gurax_pushbackBuff[n] = {var};  \
for (int gurax_pushbackLevel = 1; gurax_pushbackLevel > 0; ) { \
var = gurax_pushbackBuff[--gurax_pushbackLevel];

#define Gurax_EndPushbackRegionEx() \
}

#define Gurax_PushbackEx(val) \
gurax_pushbackBuff[gurax_pushbackLevel++] = (val)

#define Gurax_PushbackCancelEx() \
gurax_pushbackLevel--

//------------------------------------------------------------------------------
// Utility macros
//------------------------------------------------------------------------------
#define Gurax_ArraySizeOf(x) (sizeof(x) / sizeof(x[0]))

namespace Gurax {

class Argument;
class Function;
class Symbol;

//------------------------------------------------------------------------------
// SortOrder
//------------------------------------------------------------------------------
enum class SortOrder { None, Ascend, Descend };

//------------------------------------------------------------------------------
// Event
//------------------------------------------------------------------------------
enum class Event { None, Break, Continue };

//------------------------------------------------------------------------------
// SearchMode
//------------------------------------------------------------------------------
enum class SearchMode { DepthFirst, BreadthFirst };

//------------------------------------------------------------------------------
// Endian
//------------------------------------------------------------------------------
enum class Endian { Little, Big };

//------------------------------------------------------------------------------
// CustomPtr
//------------------------------------------------------------------------------
template<typename T> class CustomPtr {
protected:
	T* _p;
public:
	// Default constructor
	CustomPtr(T* p) : _p(p) {}
	// Copy constructor/operator
	CustomPtr(const CustomPtr& obj) = delete;
	CustomPtr& operator=(const CustomPtr& obj) = delete;
	// Move constructor/operator
	CustomPtr(CustomPtr&& obj) = delete;
	CustomPtr& operator=(CustomPtr&& obj) noexcept = delete;
	// Destructor
	~CustomPtr() = default;
public:
	T& operator*() { return *_p; }
	T& operator*() const { return *_p; }
	T* operator->() { return _p; }
	T* operator->() const { return _p; }
	T* get() { return _p; }
	T* get() const { return _p; }
	T* release() { T* p = _p; _p = nullptr; return p; }
	explicit operator bool() const { return static_cast<bool>(_p); }
};

//------------------------------------------------------------------------------
// CharSeq
//------------------------------------------------------------------------------
class CharSeq {
public:
	virtual char GetChar() = 0;
};

//------------------------------------------------------------------------------
// Number types
//------------------------------------------------------------------------------
using Bool		= bool;				// boolean
using Char		= char;				// signed 8bit
using UChar		= unsigned char;	// unsigned 8bit
using Short		= short;			// signed 16bit
using UShort	= unsigned short;	// unsigned 16bit
using Int		= int;				// signed native bits
using UInt		= unsigned int;		// unsigned native bits
using Long		= long;				// long
using ULong		= unsigned long;	// unsigned long
using Int8		= int8_t;			// signed 8bit
using UInt8		= uint8_t;			// unsigned 8bit
using Int16		= int16_t;			// signed 16bit
using UInt16	= uint16_t;			// unsigned 16bit
using Int32		= int32_t;			// signed 32bit
using UInt32	= uint32_t;			// unsigned 32bit
using Int64		= int64_t;			// signed 64bit
using UInt64	= uint64_t;			// unsigned 64bit
using Float		= float;			// floating-point number 32bit
using Double	= double;			// floating-point number 64bit

//-----------------------------------------------------------------------------
// Precedence
//-----------------------------------------------------------------------------
enum class Precedence { LT, EQ, GT, Error, };

//-----------------------------------------------------------------------------
// CRC32
//-----------------------------------------------------------------------------
class GURAX_DLLDECLARE CRC32 {
private:
	UInt32 _crc32;
	size_t _bytes;
public:
	CRC32() : _crc32(0xffffffff), _bytes(0) {}
	void Initialize() { _crc32 = 0xffffffff, _bytes = 0; }
	void Update(const void* buff, size_t bytes);
	UInt32 GetResult() const { return ~_crc32 & 0xffffffff; }
	size_t GetBytes() const { return _bytes; }
};

}

#endif
