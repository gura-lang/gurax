//==============================================================================
// Object_stream.h
//==============================================================================
#ifndef GURAX_OBJECT_STREAM_H
#define GURAX_OBJECT_STREAM_H
#include "Object.h"
#include "Stream.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Object_stream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_stream : public Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_stream);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_stream");
	// Class declaration
	class KlassEx : public Klass {
	public:
		using Klass::Klass;
		virtual void DoPrepare() override;
	};
	static KlassEx klass;
private:
	RefPtr<Stream> _pStream;
public:
	// Constructor
	Object_stream() = delete;
	explicit Object_stream(Stream *pStream) : Object(klass), _pStream(pStream) {}
	// Copy constructor/operator
	Object_stream(const Object_stream& src) : Object(klass), _pStream(src._pStream->Reference()) {}
	Object_stream& operator=(const Object_stream& src) { _pStream.reset(src._pStream->Reference()); return *this; }
	// Move constructor/operator
	Object_stream(Object_stream&& src) : Object(klass), _pStream(src._pStream.release()) {}
	Object_stream& operator=(Object_stream&& src) noexcept { _pStream.reset(src._pStream.release()); return *this; }
protected:
	// Destructor
	~Object_stream() = default;
public:
	const Stream* GetStream() const { return _pStream.get(); }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override { return reinterpret_cast<size_t>(this); }
	virtual bool IsEqualTo(const Object* pObject) const override { return IsIdentical(pObject); }
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetStream()->IsLessThan(dynamic_cast<const Object_stream*>(pObject)->GetStream()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss = StringStyle::Empty) const override {
		return _pStream->ToString(ss);
	}
};

}

#endif
