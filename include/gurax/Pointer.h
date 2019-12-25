//==============================================================================
// Pointer.h
//==============================================================================
#ifndef GURAX_POINTER_H
#define GURAX_POINTER_H
#include "Packer.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Pointer : public Packer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Pointer);
public:
	enum class ElemType {
		None, Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float, Double, String,
	};
	class SymbolAssoc_ElemType : public SymbolAssoc<ElemType, ElemType::None> {
	public:
		SymbolAssoc_ElemType() {
			Assoc(Gurax_Symbol(int8),			ElemType::Int8);
			Assoc(Gurax_Symbol(uint8),			ElemType::UInt8);
			Assoc(Gurax_Symbol(int16),			ElemType::Int16);
			Assoc(Gurax_Symbol(uint16),			ElemType::UInt16);
			Assoc(Gurax_Symbol(int32),			ElemType::Int32);
			Assoc(Gurax_Symbol(uint32),			ElemType::UInt32);
			Assoc(Gurax_Symbol(int64),			ElemType::Int64);
			Assoc(Gurax_Symbol(uint64),			ElemType::UInt64);
			Assoc(Gurax_Symbol(float_),			ElemType::Float);
			Assoc(Gurax_Symbol(double_),		ElemType::Double);
			Assoc(Gurax_Symbol(string),			ElemType::String);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_ElemType());
		}
	};
protected:
	size_t _offset;
public:
	// Constructor
	Pointer(size_t offset) : _offset(offset) {}
	// Copy constructor/operator
	Pointer(const Pointer& src) : _offset(src._offset) {}
	Pointer& operator=(const Pointer& src) = delete;
	// Move constructor/operator
	Pointer(Pointer&& src) = delete;
	Pointer& operator=(Pointer&& src) noexcept = delete;
protected:
	~Pointer() = default;
public:
	void SetOffset(size_t offset) { _offset = offset; }
	size_t GetOffset() const { return _offset; }
	size_t GetSizeAvailable() const {
		size_t bytesEntire = GetSizeEntire();
		return (_offset < bytesEntire)? bytesEntire - _offset : 0;
	}
	bool Advance(int distance);
	bool PackStay(const char* format, const ValueList& valListArg);
	Value* UnpackStay(const char* format, const ValueList& valListArg, bool exceedErrorFlag);
	bool PutValue(ElemType elemType, const Value& value);
	bool PutValues(ElemType elemType, const ValueList& valList);
	bool PutValueStay(ElemType elemType, const Value& value);
	bool PutValuesStay(ElemType elemType, const ValueList& valList);
	template<typename T, bool bigEndianFlag> bool PutStay(T num);
	template<typename T, bool bigEndianFlag> bool GetStay(T* pNum, bool exceedErrorFlag);
	bool CheckWritable() const;
public:
	virtual Pointer* Clone() const = 0;
	virtual const Value& GetTarget() const = 0;
	virtual const UInt8* GetPointerC() const = 0;
	virtual UInt8* GetWritablePointerC() const = 0;
	virtual size_t GetSizeEntire() const = 0;
	virtual bool IsWritable() const = 0;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Pointer& other) const { return this == &other; }
	bool IsEqualTo(const Pointer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Pointer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	static ElemType SymbolToElemType(const Symbol* pSymbol) {
		return SymbolAssoc_ElemType::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* ElemTypeToSymbol(ElemType elemType) {
		return SymbolAssoc_ElemType::GetInstance().ToSymbol(elemType);
	}
};

template<typename T, bool bigEndianFlag> bool Pointer::PutStay(T num)
{
	size_t offset = _offset;
	bool rtn = Put<T, bigEndianFlag>(num);
	_offset = offset;
	return rtn;
}

template<typename T, bool bigEndianFlag> bool Pointer::GetStay(T* pNum, bool exceedErrorFlag)
{
	size_t offset = _offset;
	bool rtn = Get<T, bigEndianFlag>(pNum, exceedErrorFlag);
	_offset = offset;
	return rtn;
}

}

#endif
