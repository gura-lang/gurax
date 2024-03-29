//==============================================================================
// LabelSet.h
//==============================================================================
#ifndef GURAX_MODULE_ML_CIFAR_LABELSET_H
#define GURAX_MODULE_ML_CIFAR_LABELSET_H
#include <gurax.h>

Gurax_BeginModuleScope(ml_cifar)

//------------------------------------------------------------------------------
// LabelSet
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LabelSet : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(LabelSet);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("ml.cifar.LabelSet");
private:
	Binary _labels;
	Binary _labelsSuper;
	StringList _labelNames;
	StringList _labelNamesSuper;
	size_t _nClasses;
	size_t _nClassesSuper;
public:
	// Constructor
	LabelSet() : _nClasses(0), _nClassesSuper(0) {}
	// Copy constructor/operator
	LabelSet(const LabelSet& src) = delete;
	LabelSet& operator=(const LabelSet& src) = delete;
	// Move constructor/operator
	LabelSet(LabelSet&& src) noexcept = delete;
	LabelSet& operator=(LabelSet&& src) noexcept = delete;
protected:
	~LabelSet() = default;
public:
	void Add(UInt8 label);
	void Add(UInt8 labelSuper, UInt8 label);
	UInt8 GetLabel(size_t iSample) const { return _labels[iSample]; }
	UInt8 GetLabelSuper(size_t iSample) const { return _labelsSuper[iSample]; }
	String GetLabelName(size_t iSample) const;
	String GetLabelNameSuper(size_t iSample) const;
	void SetLabelNames(StringList labelNames) { _labelNames = labelNames; }
	void SetLabelNamesSuper(StringList labelNamesSuper) { _labelNamesSuper = labelNamesSuper; }
	size_t GetNClasses() const { return _nClasses; }
	size_t GetNClassesSuper() const { return _nClassesSuper; }
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const LabelSet& other) const { return this == &other; }
	bool IsEqualTo(const LabelSet& other) const { return IsIdentical(other); }
	bool IsLessThan(const LabelSet& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// LabelSetList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LabelSetList : public ListBase<LabelSet*> {
};

//------------------------------------------------------------------------------
// LabelSetOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE LabelSetOwner : public LabelSetList {
public:
	~LabelSetOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(ml_cifar)

#endif
