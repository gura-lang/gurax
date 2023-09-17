//==============================================================================
// Pointer.h
//==============================================================================
#ifndef GURAX_POINTER_H
#define GURAX_POINTER_H
#include "Packer.h"

namespace Gurax {

class Iterator;

//------------------------------------------------------------------------------
// Pointer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Pointer : public Packer {
public:
	// Referable declaration
	Gurax_DeclareReferable(Pointer);
protected:
	const ElemType& _elemType;
	size_t _offset;
public:
	// Constructor
	Pointer(const ElemType& elemType, size_t offset) : _elemType(elemType), _offset(offset) {}
	// Copy constructor/operator
	Pointer(const Pointer& src) : _elemType(src._elemType), _offset(src._offset) {}
	Pointer& operator=(const Pointer& src) = delete;
	// Move constructor/operator
	Pointer(Pointer&& src) = delete;
	Pointer& operator=(Pointer&& src) noexcept = delete;
protected:
	~Pointer() = default;
public:
	static void Bootup();
public:
	const ElemType& GetElemType() const { return _elemType; }
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
};

}

#endif
