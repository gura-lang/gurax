//==============================================================================
// BasicPointer.h
//==============================================================================
#ifndef GURAX_BASICPOINTER_H
#define GURAX_BASICPOINTER_H
#include "VType_Binary.h"
#include "Pointer.h"

namespace Gurax {

//------------------------------------------------------------------------------
// Pointer_String
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Pointer_String : public Pointer {
protected:
	RefPtr<StringReferable> _pString;
public:
	Pointer_String(StringReferable* pString, size_t offset = 0);
	Pointer_String(const Pointer_String& src);
public:
	const char* GetString() const { return _pString->GetString(); }
	const String& GetStringSTL() const { return _pString->GetStringSTL(); }
public:
	// Virtual functions of Packer
	virtual bool StorePrepare(size_t bytes) override { return false; }
	virtual void StoreBuffer(const void* buff, size_t bytes, bool forwardFlag) override {}
	virtual const UInt8* ExtractPrepare(size_t bytes, bool forwardFlag) override;
public:
	// Virtual functions of Pointer
	virtual Pointer* Clone() const override { return new Pointer_String(*this); }
	virtual const char* GetName() const override { return "String"; }
	virtual const void* GetPointerToTarget() const override { return _pString.get(); }
	virtual const void* DoGetPointerC() const override;
	virtual void* DoGetWritablePointerC() const override;
	virtual size_t GetBytesEntire() const override;
	virtual bool IsWritable() const override;
};

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
	virtual void StoreBuffer(const void* buff, size_t bytes, bool forwardFlag) override;
	virtual const UInt8* ExtractPrepare(size_t bytes, bool forwardFlag) override;
public:
	// Virtual functions of Pointer
	virtual Pointer* Clone() const override { return new Pointer_Binary(*this); }
	virtual const char* GetName() const override { return "Binary"; }
	virtual const void* GetPointerToTarget() const override { return _pBinary.get(); }
	virtual const void* DoGetPointerC() const override;
	virtual void* DoGetWritablePointerC() const override;
	virtual size_t GetBytesEntire() const override;
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
	virtual void StoreBuffer(const void* buff, size_t bytes, bool forwardFlag) override;
	virtual const UInt8* ExtractPrepare(size_t bytes, bool forwardFlag) override;
public:
	// Virtual functions of Pointer
	virtual Pointer* Clone() const override { return new Pointer_Memory(*this); }
	virtual const char* GetName() const override { return "Memory"; }
	virtual const void* GetPointerToTarget() const override { return _pMemory.get(); }
	virtual const void* DoGetPointerC() const override;
	virtual void* DoGetWritablePointerC() const override;
	virtual size_t GetBytesEntire() const override;
	virtual bool IsWritable() const override;
};

}

#endif
