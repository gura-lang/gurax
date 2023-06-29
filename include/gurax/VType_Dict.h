//==============================================================================
// VType_Dict.h
//==============================================================================
#ifndef GURAX_VTYPE_DICT_H
#define GURAX_VTYPE_DICT_H
#include "VType_Object.h"
#include "ValueDict.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Dict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Dict : public VType {
public:
	static const SerialId serialId = 0x00000006;
public:
	VType_Dict() : VType(serialId) {}
	explicit VType_Dict(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_Dict(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_Dict VTYPE_Dict;

//------------------------------------------------------------------------------
// Value_Dict
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Dict : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Dict);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Dict");
protected:
	RefPtr<ValueDict> _pValueDict;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Dict(VType& vtype = VTYPE_Dict) :
		Value_Dict(new ValueDict(), vtype) {}
	explicit Value_Dict(ValueDict* pValueDict, VType& vtype = VTYPE_Dict) :
		Value_Object(vtype), _pValueDict(pValueDict) {}
	// Copy constructor/operator
	Value_Dict(const Value_Dict& src) :
		Value_Object(src), _pValueDict(src._pValueDict->CloneDeep()) {}
	Value_Dict& operator=(const Value_Dict& src) = delete;
	// Move constructor/operator
	Value_Dict(Value_Dict&& src) = delete;
	Value_Dict& operator=(Value_Dict&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Dict() = default;
public:
	ValueDict& GetValueDict() { return *_pValueDict; }
	const ValueDict& GetValueDict() const { return *_pValueDict; }
public:
	static ValueDict& GetValueDict(Value& value) {
		return dynamic_cast<Value_Dict&>(value).GetValueDict();
	}
	static const ValueDict& GetValueDict(const Value& value) {
		return dynamic_cast<const Value_Dict&>(value).GetValueDict();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return new Value_Dict(*this); }
	virtual size_t DoCalcHash() const override { return GetValueDict().CalcHash(); }
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetValueDict().IsEqualTo(dynamic_cast<const Value_Dict&>(value).GetValueDict());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetValueDict().IsLessThan(dynamic_cast<const Value_Dict&>(value).GetValueDict()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
		
	}
	virtual String ToString(const StringStyle& ss) const override;
public:
	virtual bool DoEmptyIndexGet(Value** ppValue) const override;
	virtual bool DoEmptyIndexSet(RefPtr<Value> pValue) override;
	virtual bool DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const override;
	virtual bool DoSingleIndexSet(const Value& valueIndex, RefPtr<Value> pValue) override;
	virtual bool DoSerialize(Stream& stream) const override;
};

}

#endif
