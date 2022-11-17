//==============================================================================
// Packer.h
//==============================================================================
#ifndef GURAX_PACKER_H
#define GURAX_PACKER_H
#include "Referable.h"

namespace Gurax {

class Pointer;

//------------------------------------------------------------------------------
// Packer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Packer : public Referable {
public:
	Gurax_DeclareReferable(Packer)
public:
	Packer() {}
protected:
	virtual ~Packer() = default;
public:
	bool Pack(const char* format, const ValueList& valListArg);
	Value* Unpack(const char* format, const ValueList& valListArg, bool exceedErrorFlag);
	template<typename T, bool bigEndianFlag> bool Put(T num);
	template<typename T, bool bigEndianFlag> bool Get(T* pNum, bool exceedErrorFlag);
	bool PutBuffer(const void* buff, size_t bytes);
	bool PutPointer(const Pointer& pointer);
	bool PutPointer(const Pointer& pointer, size_t bytes);
public:
	virtual bool StorePrepare(size_t bytes) = 0;
	virtual void StoreBuffer(const void* buff, size_t bytes) = 0;
	virtual const UInt8* ExtractPrepare(size_t bytes) = 0;
private:
	template<typename T, bool bigEndianFlag> void Store(T num);
	template<typename T, bool bigEndianFlag> T Extract(const UInt8* pByte);
};

template<typename T, bool bigEndianFlag> bool Packer::Put(T num)
{
	if (!StorePrepare(sizeof(T))) return false;
	Store<T, bigEndianFlag>(num);
	return true;
}

template<typename T, bool bigEndianFlag> bool Packer::Get(T* pNum, bool exceedErrorFlag)
{
	const UInt8* pByte = ExtractPrepare(sizeof(T));
	if (!pByte) {
		if (exceedErrorFlag) Error::Issue(ErrorType::RangeError, "exceeds the range");
		return false;
	}
	*pNum = Extract<T, bigEndianFlag>(pByte);
	return true;
}

template<> inline void Packer::Store<UInt8, true>(UInt8 num)
{
	StoreBuffer(&num, sizeof(UInt8));
}

template<> inline void Packer::Store<UInt8, false>(UInt8 num)
{
	StoreBuffer(&num, sizeof(UInt8));
}

template<> inline void Packer::Store<Int8, true>(Int8 num)
{
	Store<UInt8, true>(static_cast<UInt8>(num));
}

template<> inline void Packer::Store<Int8, false>(Int8 num)
{
	Store<UInt8, false>(static_cast<UInt8>(num));
}

template<> inline void Packer::Store<UInt16, true>(UInt16 num)
{
	UInt8 buff[sizeof(UInt16)];
	UInt8* pByte = buff + sizeof(UInt16) - 1;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte   = static_cast<UInt8>(num);
	StoreBuffer(buff, sizeof(UInt16));
}

template<> inline void Packer::Store<UInt16, false>(UInt16 num)
{
	UInt8 buff[sizeof(UInt16)];
	UInt8* pByte = buff;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte   = static_cast<UInt8>(num);
	StoreBuffer(buff, sizeof(UInt16));
}

template<> inline void Packer::Store<Int16, true>(Int16 num)
{
	Store<UInt16, true>(static_cast<UInt16>(num));
}

template<> inline void Packer::Store<Int16, false>(Int16 num)
{
	Store<UInt16, false>(static_cast<UInt16>(num));
}

template<> inline void Packer::Store<UInt32, true>(UInt32 num)
{
	UInt8 buff[sizeof(UInt32)];
	UInt8* pByte = buff + sizeof(UInt32) - 1;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte   = static_cast<UInt8>(num);
	StoreBuffer(buff, sizeof(UInt32));
}

template<> inline void Packer::Store<UInt32, false>(UInt32 num)
{
	UInt8 buff[sizeof(UInt32)];
	UInt8* pByte = buff;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte   = static_cast<UInt8>(num);
	StoreBuffer(buff, sizeof(UInt32));
}

template<> inline void Packer::Store<Int32, true>(Int32 num)
{
	Store<UInt32, true>(static_cast<UInt32>(num));
}

template<> inline void Packer::Store<Int32, false>(Int32 num)
{
	Store<UInt32, false>(static_cast<UInt32>(num));
}

template<> inline void Packer::Store<UInt64, true>(UInt64 num)
{
	UInt8 buff[sizeof(UInt64)];
	UInt8* pByte = buff + sizeof(UInt64) - 1;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte   = static_cast<UInt8>(num);
	StoreBuffer(buff, sizeof(UInt64));
}

template<> inline void Packer::Store<UInt64, false>(UInt64 num)
{
	UInt8 buff[sizeof(UInt64)];
	UInt8* pByte = buff;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte   = static_cast<UInt8>(num);
	StoreBuffer(buff, sizeof(UInt64));
}

template<> inline void Packer::Store<Int64, true>(Int64 num)
{
	Store<UInt64, true>(static_cast<UInt64>(num));
}

template<> inline void Packer::Store<Int64, false>(Int64 num)
{
	Store<UInt64, false>(static_cast<UInt64>(num));
}

template<> inline void Packer::Store<Float, true>(Float num)
{
	Store<UInt32, true>(*reinterpret_cast<UInt32*>(&num));
}

template<> inline void Packer::Store<Float, false>(Float num)
{
	Store<UInt32, false>(*reinterpret_cast<UInt32*>(&num));
}

template<> inline void Packer::Store<Double, true>(Double num)
{
	Store<UInt64, true>(*reinterpret_cast<UInt64*>(&num));
}

template<> inline void Packer::Store<Double, false>(Double num)
{
	Store<UInt64, false>(*reinterpret_cast<UInt64*>(&num));
}

template<> inline UInt8 Packer::Extract<UInt8, true>(const UInt8* pByte)
{
	return *pByte;
}

template<> inline UInt8 Packer::Extract<UInt8, false>(const UInt8* pByte)
{
	return *pByte;
}

template<> inline Int8 Packer::Extract<Int8, true>(const UInt8* pByte)
{
	return static_cast<Int8>(Extract<UInt8, true>(pByte));
}

template<> inline Int8 Packer::Extract<Int8, false>(const UInt8* pByte)
{
	return static_cast<Int8>(Extract<UInt8, false>(pByte));
}

template<> inline UInt16 Packer::Extract<UInt16, true>(const UInt8* pByte)
{
	UInt16 num = 0;
	num = num        + *pByte; pByte++;
	num = (num << 8) + *pByte;
	return num;
}

template<> inline UInt16 Packer::Extract<UInt16, false>(const UInt8* pByte)
{
	UInt16 num = 0;
	pByte += sizeof(UInt16) - 1;
	num = num        + *pByte; pByte--;
	num = (num << 8) + *pByte;
	return num;
}

template<> inline Int16 Packer::Extract<Int16, true>(const UInt8* pByte)
{
	return static_cast<Int16>(Extract<UInt16, true>(pByte));
}

template<> inline Int16 Packer::Extract<Int16, false>(const UInt8* pByte)
{
	return static_cast<Int16>(Extract<UInt16, false>(pByte));
}

template<> inline UInt32 Packer::Extract<UInt32, true>(const UInt8* pByte)
{
	UInt32 num = 0;
	num = num        + *pByte; pByte++;
	num = (num << 8) + *pByte; pByte++;
	num = (num << 8) + *pByte; pByte++;
	num = (num << 8) + *pByte;
	return num;
}

template<> inline UInt32 Packer::Extract<UInt32, false>(const UInt8* pByte)
{
	UInt32 num = 0;
	pByte += sizeof(UInt32) - 1;
	num = num        + *pByte; pByte--;
	num = (num << 8) + *pByte; pByte--;
	num = (num << 8) + *pByte; pByte--;
	num = (num << 8) + *pByte;
	return num;
}

template<> inline Int32 Packer::Extract<Int32, true>(const UInt8* pByte)
{
	return static_cast<Int32>(Extract<UInt32, true>(pByte));
}

template<> inline Int32 Packer::Extract<Int32, false>(const UInt8* pByte)
{
	return static_cast<Int32>(Extract<UInt32, false>(pByte));
}

template<> inline UInt64 Packer::Extract<UInt64, true>(const UInt8* pByte)
{
	UInt64 num = 0;
	num = num        + *pByte; pByte++;
	num = (num << 8) + *pByte; pByte++;
	num = (num << 8) + *pByte; pByte++;
	num = (num << 8) + *pByte; pByte++;
	num = (num << 8) + *pByte; pByte++;
	num = (num << 8) + *pByte; pByte++;
	num = (num << 8) + *pByte; pByte++;
	num = (num << 8) + *pByte;
	return num;
}

template<> inline UInt64 Packer::Extract<UInt64, false>(const UInt8* pByte)
{
	UInt64 num = 0;
	pByte += sizeof(UInt64) - 1;
	num = num        + *pByte; pByte--;
	num = (num << 8) + *pByte; pByte--;
	num = (num << 8) + *pByte; pByte--;
	num = (num << 8) + *pByte; pByte--;
	num = (num << 8) + *pByte; pByte--;
	num = (num << 8) + *pByte; pByte--;
	num = (num << 8) + *pByte; pByte--;
	num = (num << 8) + *pByte;
	return num;
}

template<> inline Int64 Packer::Extract<Int64, true>(const UInt8* pByte)
{
	return static_cast<Int64>(Extract<UInt64, true>(pByte));
}

template<> inline Int64 Packer::Extract<Int64, false>(const UInt8* pByte)
{
	return static_cast<Int64>(Extract<UInt64, false>(pByte));
}

template<> inline Float Packer::Extract<Float, true>(const UInt8* pByte)
{
	UInt32 num = Extract<UInt32, true>(pByte);
	return *reinterpret_cast<Float*>(&num);
}

template<> inline Float Packer::Extract<Float, false>(const UInt8* pByte)
{
	UInt32 num = Extract<UInt32, false>(pByte);
	return *reinterpret_cast<Float*>(&num);
}

template<> inline Double Packer::Extract<Double, true>(const UInt8* pByte)
{
	UInt64 num = Extract<UInt64, true>(pByte);
	return *reinterpret_cast<Double*>(&num);
}

template<> inline Double Packer::Extract<Double, false>(const UInt8* pByte)
{
	UInt64 num = Extract<UInt64, false>(pByte);
	return *reinterpret_cast<Double*>(&num);
}

}

#endif
