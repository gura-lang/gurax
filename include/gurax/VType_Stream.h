//==============================================================================
// VType_Stream.h
//==============================================================================
#ifndef GURAX_VTYPE_STREAM_H
#define GURAX_VTYPE_STREAM_H
#include "VType_Object.h"
#include "Stream.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Stream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Stream : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Stream VTYPE_Stream;

//------------------------------------------------------------------------------
// Value_Stream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Stream : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Stream);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Stream");
protected:
	RefPtr<Stream> _pStream;
public:
	static VType& vtype;
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
	static Stream& GetStream(Value& value) {
		return dynamic_cast<Value_Stream&>(value).GetStream();
	}
	static const Stream& GetStream(const Value& value) {
		return dynamic_cast<const Value_Stream&>(value).GetStream();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetStream().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetStream().IsEqualTo(Value_Stream::GetStream(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetStream().IsLessThan(Value_Stream::GetStream(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDigest(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
};

}

#endif
