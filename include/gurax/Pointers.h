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
	RefPtr<BinaryReferable> _pBinary;
public:
	Pointer_Binary(BinaryReferable* pBinary, size_t offset = 0);
	Pointer_Binary(const Pointer_Binary& src);
public:
	Binary& GetBinary() { return _pBinary->GetBinary(); }
	const Binary& GetBinary() const { return _pBinary->GetBinary(); }
public:
	// Virtual functions of Packer
	virtual bool StorePrepare(size_t bytes) override;
	virtual void StoreBuffer(const void* buff, size_t bytes) override;
	virtual const UInt8* ExtractPrepare(size_t bytes) override;
public:
	// Virtual functions of Pointer
	virtual Pointer* Clone() const override { return new Pointer_Binary(*this); }
	virtual const void* GetPointerToTarget() const override { return _pBinary.get(); }
	virtual const UInt8* GetPointerC() const override;
	virtual UInt8* GetWritablePointerC() const override;
	virtual size_t GetSizeEntire() const override;
	virtual bool IsWritable() const override;
};

//------------------------------------------------------------------------------
// Pointer_Memory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Pointer_Memory : public Pointer {
protected:
	RefPtr<Memory> _pMemory;
public:
	Pointer_Memory(Memory* pMemory, size_t offset = 0);
	Pointer_Memory(const Pointer_Memory& src);
public:
	Memory& GetMemory() { return *_pMemory; }
	const Memory& GetMemory() const { return *_pMemory; }
public:
	// Virtual functions of Packer
	virtual bool StorePrepare(size_t bytes) override;
	virtual void StoreBuffer(const void* buff, size_t bytes) override;
	virtual const UInt8* ExtractPrepare(size_t bytes) override;
public:
	// Virtual functions of Pointer
	virtual Pointer* Clone() const override { return new Pointer_Memory(*this); }
	virtual const void* GetPointerToTarget() const override { return _pMemory.get(); }
	virtual const UInt8* GetPointerC() const override;
	virtual UInt8* GetWritablePointerC() const override;
	virtual size_t GetSizeEntire() const override;
	virtual bool IsWritable() const override;
};

}

#endif
