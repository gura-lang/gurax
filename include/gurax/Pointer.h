//==============================================================================
// Pointer.h
//==============================================================================
#ifndef GURAX_POINTER_H
#define GURAX_POINTER_H
#include "Referable.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Pointer : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Pointer);
protected:
	size_t _offset;
public:
	// Constructor
	Pointer(size_t offset) {}
	// Copy constructor/operator
	Pointer(const Pointer& src) {}
	Pointer& operator=(const Pointer& src) = delete;
	// Move constructor/operator
	Pointer(Pointer&& src) = delete;
	Pointer& operator=(Pointer&& src) noexcept = delete;
protected:
	~Pointer() = default;
public:
#if 0
	void SetOffset(size_t offset) { _offset = offset; }
	size_t GetOffset() const { return _offset; }
	size_t GetSize() const {
		size_t bytesEntire = GetEntireSize();
		return (_offset < bytesEntire)? bytesEntire - _offset : 0;
	}
	bool Advance(int distance);
	bool PackStay(const char *format, const ValueList& valListArg);
	Value UnpackStay(const char *format, const ValueList& valListArg, bool exeedErrorFlag);
	template<typename T> bool PutStay(Environment &env, T num, bool bigEndianFlag) {
		size_t offset = _offset;
		bool rtn = Put<T>(num, bigEndianFlag);
		_offset = offset;
		return rtn;
	}
	template<typename T> bool GetStay(Environment &env, T *pNum, bool bigEndianFlag, bool exceedErrorFlag) {
		size_t offset = _offset;
		bool rtn = Get<T>(pNum, bigEndianFlag, exceedErrorFlag);
		_offset = offset;
		return rtn;
	}
#endif
public:
#if 0
	virtual Pointer* Clone() const = 0;
	//virtual Object* GetTarget() const = 0;
	virtual const UInt8* GetPointerC() const = 0;
	virtual UInt8* GetWritablePointerC() const = 0;
	virtual size_t GetEntireSize() const = 0;
	virtual bool IsWritable() const = 0;
#endif
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Pointer& other) const { return this == &other; }
	bool IsEqualTo(const Pointer& other) const { return IsIdentical(other); }
	bool IsLessThan(const Pointer& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

}

#endif
