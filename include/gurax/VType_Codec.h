//==============================================================================
// VType_Codec.h
//==============================================================================
#ifndef GURAX_VTYPE_CODEC_H
#define GURAX_VTYPE_CODEC_H
#include "VType_Object.h"
#include "Codec.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Codec
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Codec : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const override;
};

extern GURAX_DLLDECLARE VType_Codec VTYPE_Codec;

//------------------------------------------------------------------------------
// Value_Codec
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Codec : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Codec);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Codec");
protected:
	RefPtr<Codec> _pCodec;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Codec() = delete;
	Value_Codec(Codec* pCodec, VType& vtype = VTYPE_Codec) :
		Value_Object(vtype), _pCodec(pCodec) {}
	// Copy constructor/operator
	Value_Codec(const Value_Codec& src) :
		Value_Object(src), _pCodec(src._pCodec->Reference()) {}
	Value_Codec& operator=(const Value_Codec& src) = delete;
	// Move constructor/operator
	Value_Codec(Value_Codec&& src) = delete;
	Value_Codec& operator=(Value_Codec&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Codec() = default;
public:
	Codec& GetCodec() { return *_pCodec; }
	const Codec& GetCodec() const { return *_pCodec; }
public:
	static Codec& GetCodec(Value& value) {
		return dynamic_cast<Value_Codec&>(value).GetCodec();
	}
	static const Codec& GetCodec(const Value& value) {
		return dynamic_cast<const Value_Codec&>(value).GetCodec();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetCodec().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetCodec().IsEqualTo(Value_Codec::GetCodec(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetCodec().IsLessThan(Value_Codec::GetCodec(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
