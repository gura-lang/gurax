//==============================================================================
// VType_ImageDescriptor.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_VTYPE_IMAGEDESCRIPTOR_H
#define GURAX_MODULE_GIF_VTYPE_IMAGEDESCRIPTOR_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// VType_ImageDescriptor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_ImageDescriptor : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_ImageDescriptor VTYPE_ImageDescriptor;

//------------------------------------------------------------------------------
// Value_ImageDescriptor
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_ImageDescriptor : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_ImageDescriptor);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_ImageDescriptor");
protected:
	RefPtr<Content::GraphicBlock> _pGraphicBlock;
public:
	static VType& vtype;
public:
	// Constructor
	Value_ImageDescriptor() = delete;
	explicit Value_ImageDescriptor(Content::GraphicBlock* pGraphicBlock, VType& vtype = VTYPE_ImageDescriptor) :
		Value_Object(vtype), _pGraphicBlock(pGraphicBlock) {}
	// Copy constructor/operator
	Value_ImageDescriptor(const Value_ImageDescriptor& src) :
		Value_Object(src), _pGraphicBlock(src._pGraphicBlock->Reference()) {}
	Value_ImageDescriptor& operator=(const Value_ImageDescriptor& src) = delete;
	// Move constructor/operator
	Value_ImageDescriptor(Value_ImageDescriptor&& src) noexcept = delete;
	Value_ImageDescriptor& operator=(Value_ImageDescriptor&& src) noexcept = delete;
protected:
	// Destructor
	~Value_ImageDescriptor() = default;
public:
	Content::GraphicBlock& GetGraphicBlock() { return *_pGraphicBlock; }
	const Content::GraphicBlock& GetGraphicBlock() const { return *_pGraphicBlock; }
public:
	static Content::GraphicBlock& GetGraphicBlock(Value& value) {
		return dynamic_cast<Value_ImageDescriptor&>(value).GetGraphicBlock();
	}
	static const Content::GraphicBlock& GetGraphicBlock(const Value& value) {
		return dynamic_cast<const Value_ImageDescriptor&>(value).GetGraphicBlock();
	}
	static Content::GraphicBlock* GetEntityPtr(Value& value) { return &GetGraphicBlock(value); }
	static const Content::GraphicBlock* GetEntityPtr(const Value& value) { return &GetGraphicBlock(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetGraphicBlock().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetGraphicBlock().IsEqualTo(Value_ImageDescriptor::GetGraphicBlock(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetGraphicBlock().IsLessThan(Value_ImageDescriptor::GetGraphicBlock(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
