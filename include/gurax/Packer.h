//==============================================================================
// Packer.h
//==============================================================================
#ifndef GURAX_PACKER_H
#define GURAX_PACKER_H
#include "Referable.h"

namespace Gurax {

class Attribute;
class Pointer;
class Value;
class ValueList;

//------------------------------------------------------------------------------
// Packer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Packer : public Referable {
public:
	Gurax_DeclareReferable(Packer)
public:
	class GURAX_DLLDECLARE ElemType {
	public:
		static ElemType None;
		static ElemType Bool;
		static ElemType Int8;
		static ElemType UInt8;
		static ElemType Int16;
		static ElemType UInt16;
		static ElemType Int32;
		static ElemType UInt32;
		static ElemType Int64;
		static ElemType UInt64;
		static ElemType Float;
		static ElemType Double;
		static ElemType Complex;
	public:
		const Symbol* pSymbol;
		std::function<bool (Packer& packer, const Value& value, bool bigEndianFlag, bool forwardFlag)> putFunc;
		std::function<bool (Packer& packer, RefPtr<Value>& pValue, bool exceedErrorFlag, bool bigEndianFlag, bool forwardFlag)> getFunc;
	public:
		// Constructor
		ElemType() : pSymbol(nullptr) {}
		// Copy constructor/operator
		ElemType(const ElemType& src) = delete;
		ElemType& operator=(const ElemType& src) = delete;
		// Move constructor/operator
		ElemType(ElemType&& src) = delete;
		ElemType& operator=(ElemType&& src) noexcept = delete;
	protected:
		~ElemType() = default;
	public:
		bool IsIdentical(const ElemType& elemType) const { return this == &elemType; }
		bool IsNone() const { return IsIdentical(None); }
	};
public:
	Packer() {}
protected:
	virtual ~Packer() = default;
public:
	static void Bootup();
public:
	bool Pack(const char* format, const ValueList& valListArg);
	Value* Unpack(const char* format, const ValueList& valListArg, bool exceedErrorFlag);
	bool Put(const ElemType& elemType, const Value& value, bool bigEndianFlag, bool forwardFlag) {
		return elemType.putFunc(*this, value, bigEndianFlag, forwardFlag);
	}
	bool Put(const ElemType& elemType, const Value& value, const Attribute& attr);
	bool Get(const ElemType& elemType, RefPtr<Value>& pValue, bool exceedErrorFlag, bool bigEndianFlag, bool forwardFlag) {
		return elemType.getFunc(*this, pValue, exceedErrorFlag, bigEndianFlag, forwardFlag);
	}
	bool Get(const ElemType& elemType, RefPtr<Value>& pValue, const Attribute& attr);
	bool PutBuffer(const void* buff, size_t bytes);
	bool PutPointer(const Pointer& pointer);
	bool PutPointer(const Pointer& pointer, size_t bytes);
public:
	virtual bool StorePrepare(size_t bytes) = 0;
	virtual void StoreBuffer(const void* buff, size_t bytes, bool forwardFlag) = 0;
	virtual const UInt8* ExtractPrepare(size_t bytes, bool forwardFlag) = 0;
public:
	template<typename T, bool bigEndianFlag> void Store(T num, bool forwardFlag);
	template<typename T, bool bigEndianFlag> T Extract(const UInt8* pByte);
public:
	static const ElemType& SymbolToElemType(const Symbol* pSymbol);
};

template<> inline void Packer::Store<UInt8, true>(UInt8 num, bool forwardFlag)
{
	StoreBuffer(&num, sizeof(UInt8), forwardFlag);
}

template<> inline void Packer::Store<UInt8, false>(UInt8 num, bool forwardFlag)
{
	StoreBuffer(&num, sizeof(UInt8), forwardFlag);
}

template<> inline void Packer::Store<Int8, true>(Int8 num, bool forwardFlag)
{
	Store<UInt8, true>(static_cast<UInt8>(num), forwardFlag);
}

template<> inline void Packer::Store<Int8, false>(Int8 num, bool forwardFlag)
{
	Store<UInt8, false>(static_cast<UInt8>(num), forwardFlag);
}

template<> inline void Packer::Store<Bool, true>(Bool num, bool forwardFlag)
{
	Store<UInt8, true>(static_cast<UInt8>(num), forwardFlag);
}

template<> inline void Packer::Store<Bool, false>(Bool num, bool forwardFlag)
{
	Store<UInt8, false>(static_cast<UInt8>(num), forwardFlag);
}

template<> inline void Packer::Store<UInt16, true>(UInt16 num, bool forwardFlag)
{
	UInt8 buff[sizeof(UInt16)];
	UInt8* pByte = buff + sizeof(UInt16) - 1;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte   = static_cast<UInt8>(num);
	StoreBuffer(buff, sizeof(UInt16), forwardFlag);
}

template<> inline void Packer::Store<UInt16, false>(UInt16 num, bool forwardFlag)
{
	UInt8 buff[sizeof(UInt16)];
	UInt8* pByte = buff;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte   = static_cast<UInt8>(num);
	StoreBuffer(buff, sizeof(UInt16), forwardFlag);
}

template<> inline void Packer::Store<Int16, true>(Int16 num, bool forwardFlag)
{
	Store<UInt16, true>(static_cast<UInt16>(num), forwardFlag);
}

template<> inline void Packer::Store<Int16, false>(Int16 num, bool forwardFlag)
{
	Store<UInt16, false>(static_cast<UInt16>(num), forwardFlag);
}

template<> inline void Packer::Store<UInt32, true>(UInt32 num, bool forwardFlag)
{
	UInt8 buff[sizeof(UInt32)];
	UInt8* pByte = buff + sizeof(UInt32) - 1;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte-- = static_cast<UInt8>(num); num >>= 8;
	*pByte   = static_cast<UInt8>(num);
	StoreBuffer(buff, sizeof(UInt32), forwardFlag);
}

template<> inline void Packer::Store<UInt32, false>(UInt32 num, bool forwardFlag)
{
	UInt8 buff[sizeof(UInt32)];
	UInt8* pByte = buff;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte++ = static_cast<UInt8>(num); num >>= 8;
	*pByte   = static_cast<UInt8>(num);
	StoreBuffer(buff, sizeof(UInt32), forwardFlag);
}

template<> inline void Packer::Store<Int32, true>(Int32 num, bool forwardFlag)
{
	Store<UInt32, true>(static_cast<UInt32>(num), forwardFlag);
}

template<> inline void Packer::Store<Int32, false>(Int32 num, bool forwardFlag)
{
	Store<UInt32, false>(static_cast<UInt32>(num), forwardFlag);
}

template<> inline void Packer::Store<UInt64, true>(UInt64 num, bool forwardFlag)
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
	StoreBuffer(buff, sizeof(UInt64), forwardFlag);
}

template<> inline void Packer::Store<UInt64, false>(UInt64 num, bool forwardFlag)
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
	StoreBuffer(buff, sizeof(UInt64), forwardFlag);
}

template<> inline void Packer::Store<Int64, true>(Int64 num, bool forwardFlag)
{
	Store<UInt64, true>(static_cast<UInt64>(num), forwardFlag);
}

template<> inline void Packer::Store<Int64, false>(Int64 num, bool forwardFlag)
{
	Store<UInt64, false>(static_cast<UInt64>(num), forwardFlag);
}

template<> inline void Packer::Store<Float, true>(Float num, bool forwardFlag)
{
	Store<UInt32, true>(*reinterpret_cast<UInt32*>(&num), forwardFlag);
}

template<> inline void Packer::Store<Float, false>(Float num, bool forwardFlag)
{
	Store<UInt32, false>(*reinterpret_cast<UInt32*>(&num), forwardFlag);
}

template<> inline void Packer::Store<Double, true>(Double num, bool forwardFlag)
{
	Store<UInt64, true>(*reinterpret_cast<UInt64*>(&num), forwardFlag);
}

template<> inline void Packer::Store<Double, false>(Double num, bool forwardFlag)
{
	Store<UInt64, false>(*reinterpret_cast<UInt64*>(&num), forwardFlag);
}

template<> inline void Packer::Store<Complex, true>(Complex num, bool forwardFlag)
{
	UInt8 buff[sizeof(UInt64) * 2];
	UInt8* pByte = buff + sizeof(UInt64) * 2 - 1;
	UInt64 numWk = static_cast<UInt64>(num.imag());
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte   = static_cast<UInt8>(numWk);
	numWk = static_cast<UInt64>(num.real());
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte-- = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte   = static_cast<UInt8>(numWk);
	StoreBuffer(buff, sizeof(UInt64) * 2, forwardFlag);
}

template<> inline void Packer::Store<Complex, false>(Complex num, bool forwardFlag)
{
	UInt8 buff[sizeof(UInt64) * 2];
	UInt8* pByte = buff;
	UInt64 numWk = static_cast<UInt64>(num.real());
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte   = static_cast<UInt8>(numWk);
	numWk = static_cast<UInt64>(num.imag());
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte++ = static_cast<UInt8>(numWk); numWk >>= 8;
	*pByte   = static_cast<UInt8>(numWk);
	StoreBuffer(buff, sizeof(UInt64) * 2, forwardFlag);
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

template<> inline Bool Packer::Extract<Bool, true>(const UInt8* pByte)
{
	return static_cast<Bool>(Extract<UInt8, true>(pByte));
}

template<> inline Bool Packer::Extract<Bool, false>(const UInt8* pByte)
{
	return static_cast<Bool>(Extract<UInt8, false>(pByte));
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

template<> inline Complex Packer::Extract<Complex, true>(const UInt8* pByte)
{
	return Complex(Extract<Double, true>(pByte), Extract<Double, true>(pByte + sizeof(Double)));
}

template<> inline Complex Packer::Extract<Complex, false>(const UInt8* pByte)
{
	return Complex(Extract<Double, false>(pByte), Extract<Double, false>(pByte + sizeof(Double)));
}

}

#endif
