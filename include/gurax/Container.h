//==============================================================================
// Container
//==============================================================================
#ifndef GURAX_CONTAINER_H
#define GURAX_CONTAINER_H
#include "MemoryPool.h"

namespace Gurax {

//------------------------------------------------------------------------------
// List of number types
//------------------------------------------------------------------------------
typedef std::vector<Bool,	Allocator<Bool> >	BoolList;
typedef std::vector<Char,	Allocator<Char> >	CharList;
typedef std::vector<UChar,	Allocator<UChar> >	UCharList;
typedef std::vector<Short,	Allocator<Short> >	ShortList;
typedef std::vector<UShort,	Allocator<UShort> >	UShortList;
typedef std::vector<Int,	Allocator<Int> >	IntList;
typedef std::vector<UInt,	Allocator<UInt> >	UIntList;
typedef std::vector<Long,	Allocator<Long> >	LongList;
typedef std::vector<ULong,	Allocator<ULong> >	ULongList;
typedef std::vector<Int8,	Allocator<Int8> >	Int8List;
typedef std::vector<UInt8,	Allocator<UInt8> >	UInt8List;
typedef std::vector<Int16,	Allocator<Int16> >	Int16List;
typedef std::vector<UInt16,	Allocator<UInt16> >	UInt16List;
typedef std::vector<Int32,	Allocator<Int32> >	Int32List;
typedef std::vector<UInt32,	Allocator<UInt32> >	UInt32List;
typedef std::vector<Int64,	Allocator<Int64> >	Int64List;
typedef std::vector<UInt64,	Allocator<UInt64> >	UInt64List;
typedef std::vector<Float,	Allocator<Float> >	FloatList;
typedef std::vector<Double,	Allocator<Double> >	DoubleList;

//------------------------------------------------------------------------------
// Deque of number types
//------------------------------------------------------------------------------
typedef std::deque<Bool,	Allocator<Bool> >	BoolDeque;
typedef std::deque<Char,	Allocator<Char> >	CharDeque;
typedef std::deque<UChar,	Allocator<UChar> >	UCharDeque;
typedef std::deque<Short,	Allocator<Short> >	ShortDeque;
typedef std::deque<UShort,	Allocator<UShort> >	UShortDeque;
typedef std::deque<Int,		Allocator<Int> >	IntDeque;
typedef std::deque<UInt,	Allocator<UInt> >	UIntDeque;
typedef std::deque<Long,	Allocator<Long> >	LongDeque;
typedef std::deque<ULong,	Allocator<ULong> >	ULongDeque;
typedef std::deque<Int8,	Allocator<Int8> >	Int8Deque;
typedef std::deque<UInt8,	Allocator<UInt8> >	UInt8Deque;
typedef std::deque<Int16,	Allocator<Int16> >	Int16Deque;
typedef std::deque<UInt16,	Allocator<UInt16> >	UInt16Deque;
typedef std::deque<Int32,	Allocator<Int32> >	Int32Deque;
typedef std::deque<UInt32,	Allocator<UInt32> >	UInt32Deque;
typedef std::deque<Int64,	Allocator<Int64> >	Int64Deque;
typedef std::deque<UInt64,	Allocator<UInt64> >	UInt64Deque;
typedef std::deque<Float,	Allocator<Float> >	FloatDeque;
typedef std::deque<Double,	Allocator<Double> >	DoubleDeque;

}

#endif

