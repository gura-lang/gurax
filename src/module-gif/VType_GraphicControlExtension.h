//==============================================================================
// VType_GraphicControlExtension.h
//==============================================================================
#ifndef GURAX_MODULE_GIF_VTYPE_GRAPHICCONTROLEXTENSION_H
#define GURAX_MODULE_GIF_VTYPE_GRAPHICCONTROLEXTENSION_H
#include <gurax.h>
#include "Content.h"

Gurax_BeginModuleScope(gif)

//------------------------------------------------------------------------------
// VType_GraphicControlExtension
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_GraphicControlExtension : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_GraphicControlExtension VTYPE_GraphicControlExtension;

//------------------------------------------------------------------------------
// Value_GraphicControlExtension
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_GraphicControlExtension : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_GraphicControlExtension);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_GraphicControlExtension");
protected:
	RefPtr<Content::GraphicBlock> _pGraphicBlock;
public:
	static VType& vtype;
public:
	// Constructor
	Value_GraphicControlExtension() = delete;
	explicit Value_GraphicControlExtension(Content::GraphicBlock* pGraphicBlock, VType& vtype = VTYPE_GraphicControlExtension) :
		Value_Object(vtype), _pGraphicBlock(pGraphicBlock) {}
	// Copy constructor/operator
	Value_GraphicControlExtension(const Value_GraphicControlExtension& src) :
		Value_Object(src), _pGraphicBlock(src._pGraphicBlock->Reference()) {}
	Value_GraphicControlExtension& operator=(const Value_GraphicControlExtension& src) = delete;
	// Move constructor/operator
	Value_GraphicControlExtension(Value_GraphicControlExtension&& src) noexcept = delete;
	Value_GraphicControlExtension& operator=(Value_GraphicControlExtension&& src) noexcept = delete;
protected:
	// Destructor
	~Value_GraphicControlExtension() = default;
public:
	Content::GraphicBlock& GetGraphicBlock() { return *_pGraphicBlock; }
	const Content::GraphicBlock& GetGraphicBlock() const { return *_pGraphicBlock; }
public:
	static Content::GraphicBlock& GetGraphicBlock(Value& value) {
		return dynamic_cast<Value_GraphicControlExtension&>(value).GetGraphicBlock();
	}
	static const Content::GraphicBlock& GetGraphicBlock(const Value& value) {
		return dynamic_cast<const Value_GraphicControlExtension&>(value).GetGraphicBlock();
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
			GetGraphicBlock().IsEqualTo(Value_GraphicControlExtension::GetGraphicBlock(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetGraphicBlock().IsLessThan(Value_GraphicControlExtension::GetGraphicBlock(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(gif)

#endif
