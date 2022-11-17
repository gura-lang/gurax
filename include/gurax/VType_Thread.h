//==============================================================================
// VType_Thread.h
//==============================================================================
#ifndef GURAX_VTYPE_THREAD_H
#define GURAX_VTYPE_THREAD_H
#include "VType_Object.h"
#include "OAL.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Thread
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Thread : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern GURAX_DLLDECLARE VType_Thread VTYPE_Thread;

//------------------------------------------------------------------------------
// Value_Thread
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Thread : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Thread);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Thread");
protected:
	RefPtr<OAL::Thread> _pThread;
public:
	static VType& vtype;
public:
	// Constructor
	Value_Thread() = delete;
	explicit Value_Thread(OAL::Thread* pThread, VType& vtype = VTYPE_Thread) :
		Value_Object(vtype), _pThread(pThread) {}
	// Copy constructor/operator
	Value_Thread(const Value_Thread& src) :
		Value_Object(src), _pThread(src._pThread->Reference()) {}
	Value_Thread& operator=(const Value_Thread& src) = delete;
	// Move constructor/operator
	Value_Thread(Value_Thread&& src) noexcept = delete;
	Value_Thread& operator=(Value_Thread&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Thread() = default;
public:
	OAL::Thread& GetThread() { return *_pThread; }
	const OAL::Thread& GetThread() const { return *_pThread; }
public:
	static OAL::Thread& GetThread(Value& value) {
		return dynamic_cast<Value_Thread&>(value).GetThread();
	}
	static const OAL::Thread& GetThread(const Value& value) {
		return dynamic_cast<const Value_Thread&>(value).GetThread();
	}
	static OAL::Thread* GetEntityPtr(Value& value) { return &GetThread(value); }
	static const OAL::Thread* GetEntityPtr(const Value& value) { return &GetThread(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetThread().CalcHash();
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			GetThread().IsEqualTo(Value_Thread::GetThread(value));
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			GetThread().IsLessThan(Value_Thread::GetThread(value)) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
};

}

#endif
