//==============================================================================
// VType_TTF_Font.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_TTF_FONT_H
#define GURAX_MODULE_SDL_VTYPE_TTF_FONT_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_TTF_Font
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_TTF_Font : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_TTF_Font VTYPE_TTF_Font;

//------------------------------------------------------------------------------
// Value_TTF_Font
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_TTF_Font : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_TTF_Font);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_TTF_Font");
protected:
	TTF_Font* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_TTF_Font(VType& vtype = VTYPE_TTF_Font) : Value_Object(vtype) {}
	explicit Value_TTF_Font(TTF_Font* entity, VType& vtype = VTYPE_TTF_Font) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_TTF_Font(const Value_TTF_Font& src) = delete;
	Value_TTF_Font& operator=(const Value_TTF_Font& src) = delete;
	// Move constructor/operator
	Value_TTF_Font(Value_TTF_Font&& src) noexcept = delete;
	Value_TTF_Font& operator=(Value_TTF_Font&& src) noexcept = delete;
protected:
	// Destructor
	~Value_TTF_Font() = default;
public:
	TTF_Font& GetEntity() { return *_entity; }
	const TTF_Font& GetEntity() const { return *_entity; }
	TTF_Font* GetEntityPtr() { return _entity; }
	const TTF_Font* GetEntityPtr() const { return _entity; }
public:
	static TTF_Font& GetEntity(Value& value) {
		return dynamic_cast<Value_TTF_Font&>(value).GetEntity();
	}
	static const TTF_Font& GetEntity(const Value& value) {
		return dynamic_cast<const Value_TTF_Font&>(value).GetEntity();
	}
	static TTF_Font* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_TTF_Font&>(value).GetEntityPtr();
	}
	static const TTF_Font* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_TTF_Font&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_TTF_Font::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_TTF_Font::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
