//==============================================================================
// VType_GraphicBlock.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_VTYPE_GraphicBlock_H
#define GURAX_MODULE_GIF_VTYPE_GraphicBlock_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// VType_GraphicBlock
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GraphicBlock : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GraphicBlock VTYPE_GraphicBlock;

//------------------------------------------------------------------------------
// Value_GraphicBlock
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GraphicBlock : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GraphicBlock);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GraphicBlock");
protected:
	RefPtr<Content::GraphicBlock> _pGraphicBlock;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GraphicBlock() = delete;
	explicit Value_GraphicBlock(Content::GraphicBlock* pGraphicBlock, VType& vtype = VTYPE_GraphicBlock) :
		Value_Object(vtype), _pGraphicBlock(pGraphicBlock) {}
	// Copy constructor/operator
	Value_GraphicBlock(const Value_GraphicBlock& src) :
		Value_Object(src), _pGraphicBlock(src._pGraphicBlock->Reference()) {}
	Value_GraphicBlock& operator=(const Value_GraphicBlock& src) = delete;
	// Move constructor/operator
	Value_GraphicBlock(Value_GraphicBlock&& src) noexcept = delete;
	Value_GraphicBlock& operator=(Value_GraphicBlock&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GraphicBlock() = default;
public:
	Content::GraphicBlock& GetGraphicBlock() { return *_pGraphicBlock; }
	const Content::GraphicBlock& GetGraphicBlock() const { return *_pGraphicBlock; }
	Content::GraphicBlock* GetGraphicBlockPtr() { return _pGraphicBlock.get(); }
	const Content::GraphicBlock* GetGraphicBlockPtr() const { return _pGraphicBlock.get(); }
public:
	static Content::GraphicBlock& GetGraphicBlock(Value& value) {
		return dynamic_cast<Value_GraphicBlock&>(value).GetGraphicBlock();
	}
	static const Content::GraphicBlock& GetGraphicBlock(const Value& value) {
		return dynamic_cast<const Value_GraphicBlock&>(value).GetGraphicBlock();
	}
	static Content::GraphicBlock* GetGraphicBlockPtr(Value& value) { return &GetGraphicBlock(value); }
	static const Content::GraphicBlock* GetGraphicBlockPtr(const Value& value) { return &GetGraphicBlock(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetGraphicBlockPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetGraphicBlockPtr() == Value_GraphicBlock::GetGraphicBlockPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetGraphicBlockPtr() < Value_GraphicBlock::GetGraphicBlockPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
