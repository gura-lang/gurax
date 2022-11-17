//==============================================================================
// VType_SDL_AudioSpec.h
//==============================================================================
#ifndef GURAX_MODULE_SDL_VTYPE_SDL_AUDIOSPEC_H
#define GURAX_MODULE_SDL_VTYPE_SDL_AUDIOSPEC_H
#include "module-sdl.h"

Gurax_BeginModuleScope(sdl)

//------------------------------------------------------------------------------
// VType_SDL_AudioSpec
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_SDL_AudioSpec : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_SDL_AudioSpec VTYPE_SDL_AudioSpec;

//------------------------------------------------------------------------------
// Value_SDL_AudioSpec
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_SDL_AudioSpec : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_SDL_AudioSpec);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_SDL_AudioSpec");
protected:
	SDL_AudioSpec _entity;
	RefPtr<Processor> _pProcessor;
	RefPtr<Function> _pFuncAudioCallback;
	RefPtr<Value> _pValueUserdata;
public:
	static VType& vtype;
public:
	// Constructor
	explicit Value_SDL_AudioSpec(Processor* pProcessor, VType& vtype = VTYPE_SDL_AudioSpec);
	explicit Value_SDL_AudioSpec(const SDL_AudioSpec& entity, Processor* pProcessor, VType& vtype = VTYPE_SDL_AudioSpec);
	// Copy constructor/operator
	Value_SDL_AudioSpec(const Value_SDL_AudioSpec& src) = delete;
	Value_SDL_AudioSpec& operator=(const Value_SDL_AudioSpec& src) = delete;
	// Move constructor/operator
	Value_SDL_AudioSpec(Value_SDL_AudioSpec&& src) noexcept = delete;
	Value_SDL_AudioSpec& operator=(Value_SDL_AudioSpec&& src) noexcept = delete;
protected:
	// Destructor
	~Value_SDL_AudioSpec() = default;
public:
	SDL_AudioSpec& GetEntity() { return _entity; }
	const SDL_AudioSpec& GetEntity() const { return _entity; }
	SDL_AudioSpec* GetEntityPtr() { return &_entity; }
	const SDL_AudioSpec* GetEntityPtr() const { return &_entity; }
public:
	Processor& GetProcessor() { return *_pProcessor; }
	void SetFuncAudioCallback(Function* pFuncAudioCallback) {
		_pFuncAudioCallback.reset(pFuncAudioCallback);
	}
	void SetValueUserdata(Value* pValueUserdata) {
		_pValueUserdata.reset(pValueUserdata);
	}
	Function* GetFuncAudioCallback() { return _pFuncAudioCallback.get(); }
	const Value& GetValueUserdata() { return *_pValueUserdata; }
public:
	static void AudioCallback(void* userdata, Uint8* stream, int len);
public:
	static SDL_AudioSpec& GetEntity(Value& value) {
		return dynamic_cast<Value_SDL_AudioSpec&>(value).GetEntity();
	}
	static const SDL_AudioSpec& GetEntity(const Value& value) {
		return dynamic_cast<const Value_SDL_AudioSpec&>(value).GetEntity();
	}
	static SDL_AudioSpec* GetEntityPtr(Value& value) {
		return dynamic_cast<Value_SDL_AudioSpec&>(value).GetEntityPtr();
	}
	static const SDL_AudioSpec* GetEntityPtr(const Value& value) {
		return dynamic_cast<const Value_SDL_AudioSpec&>(value).GetEntityPtr();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return reinterpret_cast<size_t>(GetEntityPtr());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetEntityPtr() == Value_SDL_AudioSpec::GetEntityPtr(value);
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetEntityPtr() < Value_SDL_AudioSpec::GetEntityPtr(value) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

Gurax_EndModuleScope(sdl)

#endif
