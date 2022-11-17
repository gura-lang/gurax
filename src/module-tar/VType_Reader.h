//==============================================================================
// VType_Reader.h
//==============================================================================
#ifndef GURAX_MODULE_TAR_VTYPE_READER_H
#define GURAX_MODULE_TAR_VTYPE_READER_H
#include <gurax.h>
#include "Reader.h"

Gurax_BeginModuleScope(tar)

//------------------------------------------------------------------------------
// VType_Reader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Reader : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Reader VTYPE_Reader;

//------------------------------------------------------------------------------
// Value_Reader
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Reader : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Reader);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Reader");
protected:
	RefPtr<Reader> _pReader;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Reader() = delete;
	explicit Value_Reader(Reader* pReader, VType& vtype = VTYPE_Reader) :
		Value_Object(vtype), _pReader(pReader) {}
	// Copy constructor/operator
	Value_Reader(const Value_Reader& src) :
		Value_Object(src), _pReader(src._pReader->Reference()) {}
	Value_Reader& operator=(const Value_Reader& src) = delete;
	// Move constructor/operator
	Value_Reader(Value_Reader&& src) noexcept = delete;
	Value_Reader& operator=(Value_Reader&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Reader() = default;
public:
	Reader& GetReader() { return *_pReader; }
	const Reader& GetReader() const { return *_pReader; }
public:
	static Reader& GetReader(Value& value) {
		return dynamic_cast<Value_Reader&>(value).GetReader();
	}
	static const Reader& GetReader(const Value& value) {
		return dynamic_cast<const Value_Reader&>(value).GetReader();
	}
	static Reader* GetEntityPtr(Value& value) { return &GetReader(value); }
	static const Reader* GetEntityPtr(const Value& value) { return &GetReader(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetReader().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetReader().IsEqualTo(Value_Reader::GetReader(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetReader().IsLessThan(Value_Reader::GetReader(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(tar)

#endif
