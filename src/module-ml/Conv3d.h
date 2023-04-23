//==============================================================================
// Conv3d.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CONV3D_H
#define GURAX_MODULE_ML_CONV3D_H
#include <gurax.h>

Gurax_BeginModuleScope(ml)

//------------------------------------------------------------------------------
// Conv3d
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Conv3d : public Gear {
public:
	// Referable declaration
	Gurax_DeclareReferable(Conv3d);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.Conv3d");
private:
	RefPtr<Array> _pArrayFwdSaved;
public:
	// Constructor
	Conv3d() {}
	// Copy constructor/operator
	Conv3d(const Conv3d& src) = delete;
	Conv3d& operator=(const Conv3d& src) = delete;
	// Move constructor/operator
	Conv3d(Conv3d&& src) noexcept = delete;
	Conv3d& operator=(Conv3d&& src) noexcept = delete;
protected:
	~Conv3d() = default;
public:
	static void Initialize();
public:
	virtual const char* GetName() const override { return "ml.Conv3d"; }
	virtual bool EvalForward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
	virtual bool EvalBackward(Processor& processor, RefPtr<Array>& pArrayRtn, const Array& array) override;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Conv3d& other) const { return this == &other; }
	bool IsEqualTo(const Conv3d& other) const { return IsIdentical(other); }
	bool IsLessThan(const Conv3d& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Conv3dList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Conv3dList : public ListBase<Conv3d*> {
};

//------------------------------------------------------------------------------
// Conv3dOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Conv3dOwner : public Conv3dList {
public:
	~Conv3dOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml)

#endif
