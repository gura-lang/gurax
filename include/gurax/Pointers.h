//==============================================================================
// Pointers.h
//==============================================================================
#ifndef GURAX_POINTERS_H
#define GURAX_POINTERS_H
#include "VType_Binary.h"
#include "Pointer.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer_Binary
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Pointer_Binary : public Pointer {
protected:
	RefPtr<Value_Binary> _pValue;
public:
	Pointer_Binary(size_t offset, Value_Binary* pValue);
	Pointer_Binary(const Pointer_Binary& src);
	Value_Binary& GetValue() { return *_pValue; }
	const Value_Binary& GetValue() const { return *_pValue; }
	Binary& GetBinary() { return _pValue->GetBinary(); }
	const Binary& GetBinary() const { return _pValue->GetBinary(); }
public:
	// Virtual functions of Packer
	virtual bool StorePrepare(size_t bytes) override;
	virtual void StoreBuffer(const void* buff, size_t bytes) override;
	virtual const UInt8* ExtractPrepare(size_t bytes) override;
public:
	// Virtual functions of Pointer
	virtual Pointer* Clone() const override { return new Pointer_Binary(*this); }
	virtual const Value& GetTarget() const override { return *_pValue; }
	virtual const UInt8* GetPointerC() const override;
	virtual UInt8* GetWritablePointerC() const override;
	virtual size_t GetEntireSize() const override;
	virtual bool IsWritable() const override;
};

}

#endif
