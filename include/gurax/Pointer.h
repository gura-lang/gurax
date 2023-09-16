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
	enum class ElemTypeId {
		None, Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Float, Double,
	};
	class ElemType {
	public:
		ElemTypeId id;
	public:
		static const ElemType None;
		static const ElemType Int8;
		static const ElemType UInt8;
		static const ElemType Int16;
		static const ElemType UInt16;
		static const ElemType Int32;
		static const ElemType UInt32;
		static const ElemType Int64;
		static const ElemType UInt64;
		static const ElemType Float;
		static const ElemType Double;
	public:
		// Constructor
		ElemType(ElemTypeId id) : id(id) {}
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
#if 0
	class GURAX_DLLDECLARE SymbolAssoc_ElemType : public SymbolAssoc<ElemTypeId, ElemTypeId::None> {
	public:
		SymbolAssoc_ElemType() {
			Assoc(Gurax_Symbol(int8),			ElemTypeId::Int8);
			Assoc(Gurax_Symbol(uint8),			ElemTypeId::UInt8);
			Assoc(Gurax_Symbol(int16),			ElemTypeId::Int16);
			Assoc(Gurax_Symbol(uint16),			ElemTypeId::UInt16);
			Assoc(Gurax_Symbol(int32),			ElemTypeId::Int32);
			Assoc(Gurax_Symbol(uint32),			ElemTypeId::UInt32);
			Assoc(Gurax_Symbol(int64),			ElemTypeId::Int64);
			Assoc(Gurax_Symbol(uint64),			ElemTypeId::UInt64);
			Assoc(Gurax_Symbol(float_),			ElemTypeId::Float);
			Assoc(Gurax_Symbol(double_),		ElemTypeId::Double);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_ElemType());
		}
	};
#endif
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
	size_t GetBytesAvailable() const {
		size_t bytesEntire = GetBytesEntire();
		return (_offset < bytesEntire)? bytesEntire - _offset : 0;
	}
	bool Advance(int distance);
	bool PutValue(const ElemType& elemType, bool bigEndianFlag, const Value& value);
	bool PutValues(const ElemType& elemType, bool bigEndianFlag, const ValueList& valList);
	bool PutValues(const ElemType& elemType, bool bigEndianFlag, Iterator& iterator);
	bool Append(const Pointer& pointer);
	bool CheckWritable() const;
	bool IsTargetIdentical(const Pointer& pointer) const {
		return GetPointerToTarget() == pointer.GetPointerToTarget();
	}
	template<typename T> const T* GetPointerC() const {
		return reinterpret_cast<const T*>(DoGetPointerC());
	}
	template<typename T> T* GetWritablePointerC() const {
		return reinterpret_cast<T*>(DoGetWritablePointerC());
	}
public:
	virtual Pointer* Clone() const = 0;
	virtual const char* GetName() const = 0;
	virtual const void* GetPointerToTarget() const = 0;
	virtual const void* DoGetPointerC() const = 0;
	virtual void* DoGetWritablePointerC() const = 0;
	virtual size_t GetBytesEntire() const = 0;
	virtual bool IsWritable() const = 0;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Pointer& other) const { return this == &other; }
	bool IsEqualTo(const Pointer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Pointer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
public:
	static const ElemType& SymbolToElemType(const Symbol* pSymbol);
	//static ElemType SymbolToElemType(const Symbol* pSymbol) {
	//	return SymbolAssoc_ElemType::GetInstance().ToAssociated(pSymbol);
	//}
	//static const Symbol* ElemTypeToSymbol(ElemType elemType) {
	//	return SymbolAssoc_ElemType::GetInstance().ToSymbol(elemType);
	//}
};

}

#endif
