//==============================================================================
// OLE.h
//==============================================================================
#ifndef GURAX_MODULE_MSWIN_OLE_H
#define GURAX_MODULE_MSWIN_OLE_H
#include <gurax.h>
#include <ATLComTime.h>				// COleDateTime
#include <atlbase.h>				// CComPtr

Gurax_BeginModuleScope(mswin)

//------------------------------------------------------------------------------
// OLE
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE OLE : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(OLE);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("mswin.OLE");
private:
	CComPtr<IDispatch> _pDispatch;
public:
	// Constructor
	OLE(IDispatch* pDispatch) : _pDispatch(pDispatch) {}
	// Copy constructor/operator
	OLE(const OLE& src) = delete;
	OLE& operator=(const OLE& src) = delete;
	// Move constructor/operator
	OLE(OLE&& src) noexcept = delete;
	OLE& operator=(OLE&& src) noexcept = delete;
protected:
	~OLE() = default;
public:
	IDispatch* GetDispatch() { return _pDispatch; }
	bool Create(const char* progID);
	bool Connect(const char* progID);
	bool ImportConstant(Frame& frame);
	HRESULT GetDispID(const char* name, DISPID& dispid);
	HRESULT GetDispIDOfNamedArg(const char* nameMethod, const char* nameArg, DISPID& dispid);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const OLE& other) const { return this == &other; }
	bool IsEqualTo(const OLE& other) const { return IsIdentical(other); }
	bool IsLessThan(const OLE& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

Gurax_EndModuleScope(mswin)

#endif
