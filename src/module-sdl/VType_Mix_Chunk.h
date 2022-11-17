//==============================================================================
// VType_Mix_Chunk.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_MIX_CHUNK_H
#define GURAX_MODULE_SDL_VTYPE_MIX_CHUNK_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_Mix_Chunk
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Mix_Chunk : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Mix_Chunk VTYPE_Mix_Chunk;

//------------------------------------------------------------------------------
// Value_Mix_Chunk
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Mix_Chunk : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Mix_Chunk);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Mix_Chunk");
protected:
	Mix_Chunk* _entity;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_Mix_Chunk(VType& vtype = VTYPE_Mix_Chunk) : Value_Object(vtype) {}
	explicit Value_Mix_Chunk(Mix_Chunk* entity, VType& vtype = VTYPE_Mix_Chunk) :
		Value_Object(vtype), _entity(entity) {}
	// Copy constructor/operator
	Value_Mix_Chunk(const Value_Mix_Chunk& src) = delete;
	Value_Mix_Chunk& operator=(const Value_Mix_Chunk& src) = delete;
	// Move constructor/operator
	Value_Mix_Chunk(Value_Mix_Chunk&& src) noexcept = delete;
	Value_Mix_Chunk& operator=(Value_Mix_Chunk&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Mix_Chunk() = default;
public:
	Mix_Chunk& GetEntity() { return *_entity; }
	const Mix_Chunk& GetEntity() const { return *_entity; }
	Mix_Chunk* GetEntityPtr() { return _entity; }
	const Mix_Chunk* GetEntityPtr() const { return _entity; }
public:
	static Mix_Chunk& GetEntity(Value& value) {
		return dynamic_cast<Value_Mix_Chunk&>(value).GetEntity();
	}
	static const Mix_Chunk& GetEntity(const Value& value) {
		return dynamic_cast<const Value_Mix_Chunk&>(value).GetEntity();
	}
	static Mix_Chunk* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_Mix_Chunk&>(value).GetEntityPtr();
	}
	static const Mix_Chunk* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_Mix_Chunk&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_Mix_Chunk::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_Mix_Chunk::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
