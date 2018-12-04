//==============================================================================
// Common.h
//==============================================================================
#ifndef GURAX_COMMON_H
#define GURAX_COMMON_H
#include <map>
#include <memory>
#include <set>
#include <utility>
#include <vector>

namespace Gurax {

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

#if 0
typedef std::vector<Int,	Allocator<Int> >	IntList;
typedef std::vector<Long,	Allocator<Long> >	LongList;
typedef std::vector<Char,	Allocator<Char> >	CharList;
typedef std::vector<Short,	Allocator<Short> >	ShortList;
typedef std::vector<Boolean,Allocator<Boolean> >BooleanList;
typedef std::vector<Int8,	Allocator<Int8> >	Int8List;
typedef std::vector<Int16,	Allocator<Int16> >	Int16List;
typedef std::vector<Int32,	Allocator<Int32> >	Int32List;
typedef std::vector<Int64,	Allocator<Int64> >	Int64List;
typedef std::vector<UInt,	Allocator<UInt> >	UIntList;
typedef std::vector<ULong,	Allocator<ULong> >	ULongList;
typedef std::vector<UChar,	Allocator<UChar> >	UCharList;
typedef std::vector<UShort,	Allocator<UShort> >	UShortList;
typedef std::vector<UInt8,	Allocator<UInt8> >	UInt8List;
typedef std::vector<UInt16,	Allocator<UInt16> >	UInt16List;
typedef std::vector<UInt32,	Allocator<UInt32> >	UInt32List;
typedef std::vector<UInt64,	Allocator<UInt64> >	UInt64List;
typedef std::vector<Float,	Allocator<Float> >	FloatList;
typedef std::vector<Double,	Allocator<Double> >	DoubleList;
typedef std::vector<Number,	Allocator<Number> >	NumberList;
typedef std::vector<size_t,	Allocator<size_t> >	SizeTList;

typedef std::deque<Int,		Allocator<Int> >	IntDeque;
typedef std::deque<Long,	Allocator<Long> >	LongDeque;
typedef std::deque<Char,	Allocator<Char> >	CharDeque;
typedef std::deque<Short,	Allocator<Short> >	ShortDeque;
typedef std::deque<Boolean,	Allocator<Boolean> >BooleanDeque;
typedef std::deque<Int8,	Allocator<Int8> >	Int8Deque;
typedef std::deque<Int16,	Allocator<Int16> >	Int16Deque;
typedef std::deque<Int32,	Allocator<Int32> >	Int32Deque;
typedef std::deque<Int64,	Allocator<Int64> >	Int64Deque;
typedef std::deque<UInt,	Allocator<UInt> >	UIntDeque;
typedef std::deque<ULong,	Allocator<ULong> >	ULongDeque;
typedef std::deque<UChar,	Allocator<UChar> >	UCharDeque;
typedef std::deque<UShort,	Allocator<UShort> >	UShortDeque;
typedef std::deque<UInt8,	Allocator<UInt8> >	UInt8Deque;
typedef std::deque<UInt16,	Allocator<UInt16> >	UInt16Deque;
typedef std::deque<UInt32,	Allocator<UInt32> >	UInt32Deque;
typedef std::deque<UInt64,	Allocator<UInt64> >	UInt64Deque;
typedef std::deque<Float,	Allocator<Float> >	FloatDeque;
typedef std::deque<Double,	Allocator<Double> >	DoubleDeque;
typedef std::deque<Number,	Allocator<Number> >	NumberDeque;
typedef std::deque<size_t,	Allocator<size_t> >	SizeTDeque;
#endif

//------------------------------------------------------------------------------
// UniquePtr
//------------------------------------------------------------------------------
template<typename T> class UniquePtr {
private:
	T* _p;
public:
	// Default constructor
	UniquePtr(T* p = nullptr) noexcept : _p(p) {}
	// Copy constructor/operator
	UniquePtr(const UniquePtr& obj) = delete;
	UniquePtr& operator=(const UniquePtr& obj) = delete;
	// Move constructor/operator
	UniquePtr(UniquePtr&& obj) : _p(obj._p) { obj._p = nullptr; }
	UniquePtr& operator=(UniquePtr&& obj) noexcept {
		T::Delete(_p);
		_p = obj._p;
		obj._p = nullptr;
		return *this;
	}
	// Destructor
	~UniquePtr() { T::Delete(_p); }
public:
	T& operator*() { return *_p; }
	T& operator*() const { return *_p; }
	T* operator->() { return _p; }
	T* operator->() const { return _p; }
	void reset(T* p = nullptr) { T::Delete(_p); _p = p; }
	T* get() { return _p; }
	T* get() const { return _p; }
	T* release() { T* p = _p; _p = nullptr; return p; }
	explicit operator bool() const { return _p != nullptr; }
};

}

#endif
