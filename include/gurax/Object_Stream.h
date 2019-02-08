//==============================================================================
// Object_Stream.h
//==============================================================================
#ifndef GURAX_OBJECT_STREAM_H
#define GURAX_OBJECT_STREAM_H
#include "Object_Object.h"
#include "Stream.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Klass_Stream
//------------------------------------------------------------------------------
class KlassT_Stream : public Klass {
public:
	using Klass::Klass;
	virtual void DoPrepare(Frame* pFrame) override;
};

extern KlassT_Stream Klass_Stream;

//------------------------------------------------------------------------------
// Object_Stream
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Object_Stream : public Object_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Object_Stream);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Object_Stream");
private:
	RefPtr<Stream> _pStream;
public:
	// Constructor
	Object_Stream() = delete;
	explicit Object_Stream(Stream *pStream, Klass& klass = Klass_Stream) :
		Object_Object(klass), _pStream(pStream) {}
	// Copy constructor/operator
	Object_Stream(const Object_Stream& src) :
		Object_Object(src), _pStream(src._pStream->Reference()) {}
	Object_Stream& operator=(const Object_Stream& src) = delete;
	// Move constructor/operator
	Object_Stream(Object_Stream&& src) = delete;
	Object_Stream& operator=(Object_Stream&& src) noexcept = delete;
protected:
	// Destructor
	~Object_Stream() = default;
public:
	Stream& GetStream() { return *_pStream; }
	const Stream& GetStream() const { return *_pStream; }
public:
	// Virtual functions of Object
	virtual Object* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetStream().CalcHash();
	}
	virtual bool IsEqualTo(const Object* pObject) const override {
		return IsSameType(pObject) &&
			GetStream().IsEqualTo(dynamic_cast<const Object_Stream*>(pObject)->GetStream());
	}
	virtual bool IsLessThan(const Object* pObject) const override {
		return IsSameType(pObject)?
			GetStream().IsLessThan(dynamic_cast<const Object_Stream*>(pObject)->GetStream()) :
			GetKlass().IsLessThan(pObject->GetKlass());
	}
	virtual String ToString(const StringStyle& ss) const override {
		return GetStream().ToString(ss);
	}
};

}

#endif
