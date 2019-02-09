//==============================================================================
// Value_Stream.h
//==============================================================================
#ifndef GURAX_OBJECT_STREAM_H
#define GURAX_OBJECT_STREAM_H
#include "Value_Object.h"
#include "Stream.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Stream
//------------------------------------------------------------------------------
class VType_Stream : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern VType_Stream VTYPE_Stream;

//------------------------------------------------------------------------------
// Value_Stream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Stream : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Stream);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Stream");
private:
	RefPtr<Stream> _pStream;
public:
	// Constructor
	Value_Stream() = delete;
	explicit Value_Stream(Stream *pStream, VType& vtype = VTYPE_Stream) :
		Value_Object(vtype), _pStream(pStream) {}
	// Copy constructor/operator
	Value_Stream(const Value_Stream& src) :
		Value_Object(src), _pStream(src._pStream->Reference()) {}
	Value_Stream& operator=(const Value_Stream& src) = delete;
	// Move constructor/operator
	Value_Stream(Value_Stream&& src) = delete;
	Value_Stream& operator=(Value_Stream&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Stream() = default;
public:
	Stream& GetStream() { return *_pStream; }
	const Stream& GetStream() const { return *_pStream; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetStream().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pValue) const override {
		return IsSameType(pValue) &&
			GetStream().IsEqualTo(dynamic_cast<const Value_Stream*>(pValue)->GetStream());
	}
	virtual bool IsLessThan(const Object* pValue) const override {
		return IsSameType(pValue)?
			GetStream().IsLessThan(dynamic_cast<const Value_Stream*>(pValue)->GetStream()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetStream().ToString(ss);
	}
};

}

#endif
