//==============================================================================
// VType_String.h
//==============================================================================
#ifndef GURAX_VTYPE_STRING_H
#define GURAX_VTYPE_STRING_H
#include "VType_Object.h"

namespace Gurax {

//------------------------------------------------------------------------------
// VType_String
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE VType_String : public VType {
public:
	class GURAX_DLLDECLARE Iterator_Each : public Iterator {
	public:
		enum class Type { String, UTF8, UTF32 };
	private:
		RefPtr<StringReferable> _pStr;
		Type _type;
		const char* _pCurrent;
	public:
		Iterator_Each(StringReferable* pStr, Type type) :
			_pStr(pStr), _type(type), _pCurrent(GetString()) {}
	public:
		const char* GetString() const { return _pStr->GetString(); }
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override {
			return Flag::Finite | Flag::LenUndetermined;
		}
		virtual size_t GetLength() const override { return -1; }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
	class GURAX_DLLDECLARE Iterator_EachLine : public Iterator {
	private:
		RefPtr<StringReferable> _pStr;
		bool _chopFlag;
		const char* _pCurrent;
	public:
		Iterator_EachLine(StringReferable* pStr, bool chopFlag) :
			_pStr(pStr), _chopFlag(chopFlag), _pCurrent(GetString()) {}
	public:
		const char* GetString() const { return _pStr->GetString(); }
	public:
		// Virtual functions of Iterator
		virtual Flags GetFlags() const override {
			return Flag::Finite | Flag::LenUndetermined;
		}
		virtual size_t GetLength() const override { return -1; }
		virtual Value* DoNextValue() override;
		virtual String ToString(const StringStyle& ss) const override;
	};
public:
	using VType::VType;
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(const Value& value, DeclArg::Flags flags) const override;
};

extern VType_String VTYPE_String;

//------------------------------------------------------------------------------
// Value_String
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Value_String : public Value_Object {
public:
	// Referable declaration
	Gurax_DeclareReferable(Value_String);
	// Uses MemoryPool allocator
	Gurax_MemoryPoolAllocator("Value_String");
protected:
	RefPtr<StringReferable> _pStr;
public:
	// Constructor
	explicit Value_String(VType& vtype = VTYPE_String) :
		Value_String(new StringReferable(), vtype) {}
	explicit Value_String(String str, VType& vtype = VTYPE_String) :
		Value_String(new StringReferable(std::move(str)), vtype) {}
	explicit Value_String(StringReferable* pStr, VType& vtype = VTYPE_String) :
		Value_Object(vtype), _pStr(pStr) {}
	// Copy constructor/operator
	Value_String(const Value_String& src) :
		Value_Object(src), _pStr(src._pStr->Reference()) {}
		Value_String& operator=(const Value_String& src) = delete;
	// Move constructor/operator
	Value_String(Value_String&& src) = delete;
	Value_String& operator=(Value_String&& src) noexcept = delete;
protected:
	// Destructor
	~Value_String() = default;
public:
	const StringReferable& GetStringReferable() const { return *_pStr; }
	const char* GetString() const { return _pStr->GetString(); }
	const String& GetStringSTL() const { return _pStr->GetStringSTL(); }
public:
	static const StringReferable& GetStringReferable(const Value& value) {
		return dynamic_cast<const Value_String&>(value).GetStringReferable();
	}
	static const char* GetString(const Value& value) {
		return dynamic_cast<const Value_String&>(value).GetString();
	}
	static const String& GetStringSTL(const Value& value) {
		return dynamic_cast<const Value_String&>(value).GetStringSTL();
	}
	static StringList GetStringList(const ValueList& values);
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return String::CalcHash(GetString());
	}
	virtual bool IsEqualTo(const Value* pValue) const override {
		return IsSameType(pValue) &&
			String::IsEqualTo(GetString(), dynamic_cast<const Value_String*>(pValue)->GetString());
	}
	virtual bool IsLessThan(const Value* pValue) const override {
		return IsSameType(pValue)?
			String::IsLessThan(GetString(), dynamic_cast<const Value_String*>(pValue)->GetString()) :
			GetVType().IsLessThan(pValue->GetVType());
	}
	virtual String ToStringDigest(const StringStyle& ss) const override;
	virtual String ToStringDetail(const StringStyle& ss) const override;
	virtual bool IsAsDictKey() const override { return true; }
	virtual bool Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const override;
};

}

#endif
