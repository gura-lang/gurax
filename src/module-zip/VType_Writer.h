//==============================================================================
// VType_Writer.h
//==============================================================================
#ifndef GURAX_MODULE_ZIP_VTYPE_WRITER_H
#define GURAX_MODULE_ZIP_VTYPE_WRITER_H
#include <gurax.h>
#include "Writer.h"

Gurax_BeginModuleScope(zip)

//------------------------------------------------------------------------------
// VType_Writer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Writer : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Writer VTYPE_Writer;

//------------------------------------------------------------------------------
// Value_Writer
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Writer : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Writer);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Writer");
protected:
	RefPtr<Writer> _pWriter;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Writer() = delete;
	explicit Value_Writer(Writer* pWriter, VType& vtype = VTYPE_Writer) :
		Value_Object(vtype), _pWriter(pWriter) {}
	// Copy constructor/operator
	Value_Writer(const Value_Writer& src) :
		Value_Object(src), _pWriter(src._pWriter->Reference()) {}
	Value_Writer& operator=(const Value_Writer& src) = delete;
	// Move constructor/operator
	Value_Writer(Value_Writer&& src) = delete;
	Value_Writer& operator=(Value_Writer&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Writer() = default;
public:
	Writer& GetWriter() { return *_pWriter; }
	const Writer& GetWriter() const { return *_pWriter; }
public:
	static Writer& GetWriter(Value& value) {
		return dynamic_cast<Value_Writer&>(value).GetWriter();
	}
	static const Writer& GetWriter(const Value& value) {
		return dynamic_cast<const Value_Writer&>(value).GetWriter();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetWriter().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetWriter().IsEqualTo(Value_Writer::GetWriter(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetWriter().IsLessThan(Value_Writer::GetWriter(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetWriter().ToString(ss);
	}
};

Gurax_EndModuleScope(zip)

#endif
