//==============================================================================
// VType_Directory.h
//==============================================================================
#ifndef GURAX_VTYPE_DIRECTORY_H
#define GURAX_VTYPE_DIRECTORY_H
#include "VType_Object.h"
#include "Directory.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_Directory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_Directory : public VType {
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
};

extern VType_Directory VTYPE_Directory;

//------------------------------------------------------------------------------
// Value_Directory
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_Directory : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_Directory);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_Directory");
protected:
	RefPtr<Directory> _pDirectory;
public:
	// Constructor
	Value_Directory() = delete;
	Value_Directory(Directory* pDirectory, VType& vtype = VTYPE_Directory) :
		Value_Object(vtype), _pDirectory(pDirectory) {}
	// Copy constructor/operator
	Value_Directory(const Value_Directory& src) :
		Value_Object(src), _pDirectory(src._pDirectory->Reference()) {}
	Value_Directory& operator=(const Value_Directory& src) = delete;
	// Move constructor/operator
	Value_Directory(Value_Directory&& src) = delete;
	Value_Directory& operator=(Value_Directory&& src) noexcept = delete;
protected:
	// Destructor
	~Value_Directory() = default;
public:
	Directory& GetDirectory() { return *_pDirectory; }
	const Directory& GetDirectory() const { return *_pDirectory; }
public:
	static Directory& GetDirectory(Value& value) {
		return dynamic_cast<Value_Directory&>(value).GetDirectory();
	}
	static const Directory& GetDirectory(const Value& value) {
		return dynamic_cast<const Value_Directory&>(value).GetDirectory();
	}
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return GetDirectory().CalcHash();
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			GetDirectory().IsEqualTo(Value_Directory::GetDirectory(*pValue));
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			GetDirectory().IsLessThan(Value_Directory::GetDirectory(*pValue)) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDetail(const StringStyle& ss) const override {
		return GetDirectory().ToString(ss);
	}
};

}

#endif
