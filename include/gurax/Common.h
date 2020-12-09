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
public:
	static const DumpStyle Empty;
public:
	explicit DumpStyle(Flags flags = Flag::None) : _flags(flags) {}
public:
	DumpStyle& SetUpperCase()	{ _flags |= Flag::UpperCase; return *this; }
	DumpStyle& UnsetUpperCase()	{ _flags &= ~Flag::UpperCase; return *this; }
	DumpStyle& SetAddrInfo()	{ _flags |= Flag::AddrInfo; return *this; }
	DumpStyle& UnsetAddrInfo()	{ _flags &= ~Flag::AddrInfo; return *this; }
	bool IsUpperCase() const	{ return (_flags & Flag::UpperCase) != 0; }
	bool IsAddrInfo() const		{ return (_flags & Flag::AddrInfo) != 0; }
public:
	static void DeclareAttrOpt(Function& func);
	static Flags ToFlags(const Argument& argument);
};

//------------------------------------------------------------------------------
// ListBase
//------------------------------------------------------------------------------
template<typename T> class ListBase {
public:
	using Container = std::vector<T>;
protected:
	Container _container;
public:
	using pointer = typename Container::pointer;
	using const_pointer = typename Container::const_pointer;
	using reference = typename Container::reference;
	using const_reference = typename Container::const_reference;
	using value_type = typename Container::value_type;
	using iterator = typename Container::iterator;
	using const_iterator = typename Container::const_iterator;
	using reverse_iterator = typename Container::reverse_iterator;
	using const_reverse_iterator = typename Container::const_reverse_iterator;
public:
	ListBase() {}
	ListBase(size_t n) : _container(n) {}
	ListBase(size_t n, T elem) : _container(n, elem) {}
	ListBase(const ListBase& src) : _container(src._container) {}
	ListBase(ListBase&& src) : _container(std::move(src._container)) {}
	ListBase(const_iterator first, const_iterator last) : _container(first, last) {}
	ListBase(std::initializer_list<T> initList) : _container(initList) {}
public:
	void operator=(const ListBase& src) { _container = src._container; }
	void operator=(ListBase&& src) { _container = std::move(src._container); }
public:
	reference operator[](size_t pos) { return _container[pos]; }
	const_reference operator[](size_t pos) const { return _container[pos]; }
	bool empty() const { return _container.empty(); }
	size_t capacity() const { return _container.capacity(); }
	size_t size() const { return _container.size(); }
	template<typename T> T sizeT() const { return static_cast<T>(_container.size()); }
	void clear() { _container.clear(); }
	void reserve(size_t size) { _container.reserve(size); }
	operator const_pointer() const { return _container.data(); }
	const_pointer data() const { return _container.data(); }
	const_reference front() const { return _container.front(); }
	const_reference back() const { return _container.back(); }
	reference front() { return _container.front(); }
	reference back() { return _container.back(); }
	iterator begin() { return _container.begin(); }
	iterator end() { return _container.end(); }
	const_iterator begin() const { return _container.begin(); }
	const_iterator end() const { return _container.end(); }
	reverse_iterator rbegin() { return _container.rbegin(); }
	reverse_iterator rend() { return _container.rend(); }
	const_reverse_iterator rbegin() const { return _container.rbegin(); }
	const_reverse_iterator rend() const { return _container.rend(); }
	reference at(size_t pos) { return _container.at(pos); }
	const_reference at(size_t pos) const { return _container.at(pos); }
	void push_back(const_reference elem) { _container.push_back(elem); }
	void pop_back() { _container.pop_back(); }
	void insert(const_iterator pos, const_reference elem) { _container.insert(pos, elem); }
	void insert(const_iterator pos, const_iterator first, const_iterator last) { _container.insert(pos, first, last); }
	void erase(const_iterator pos) { _container.erase(pos); }
	void erase(const_iterator first, const_iterator last) { _container.erase(first, last); }
public:
	template<typename T_LessThan, typename T_GreaterThan>
	void SortByOrder(SortOrder sortOrder) {
		if (sortOrder == SortOrder::Ascend) {
			std::sort(_container.begin(), _container.end(), T_LessThan());
		} else if (sortOrder == SortOrder::Descend) {
			std::sort(_container.begin(), _container.end(), T_GreaterThan());
		}
	}
	template<typename T_LessThan, typename T_GreaterThan>
	void StableSortByOrder(SortOrder sortOrder) {
		if (sortOrder == SortOrder::Ascend) {
			std::stable_sort(_container.begin(), _container.end(), T_LessThan());
		} else if (sortOrder == SortOrder::Descend) {
			std::stable_sort(_container.begin(), _container.end(), T_GreaterThan());
		}
	}
};

}

#endif
