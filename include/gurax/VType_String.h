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
	static const SerialId serialId = 0x0000001b;
public:
	template<typename T_CharCmp>
	class Iterator_Split : public Iterator {
	private:
		RefPtr<StringReferable> _pStr;
		String _sep;
		Int _cntMax;
		Int _cnt;
		bool _foundFlag;
		const char* _pCurrent;
	public:
		Iterator_Split(StringReferable* pStr, String sep, Int cntMax) :
			_pStr(pStr), _sep(sep), _cntMax(cntMax), _cnt(0), _foundFlag(false), _pCurrent(GetString()) {}
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
	class GURAX_DLLDECLARE Iterator_Fold : public Iterator {
	private:
		RefPtr<StringReferable> _pStr;
		const char* _pCurrent;
		size_t _lenPerFold;
		size_t _lenStep;
		bool _neatFlag;
	public:
		Iterator_Fold(StringReferable* pStr, size_t lenPerFold, size_t lenStep, bool neatFlag) :
			_pStr(pStr), _pCurrent(pStr->GetString()),
			_lenPerFold(lenPerFold), _lenStep(lenStep), _neatFlag(neatFlag) {}
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
	class GURAX_DLLDECLARE Iterator_Foldw : public Iterator {
	private:
		RefPtr<StringReferable> _pStr;
		const char* _pCurrent;
		size_t _widthPerFold;
		char _chPadding;
	public:
		Iterator_Foldw(StringReferable* pStr, size_t widthPerFold, char chPadding) :
			_pStr(pStr), _pCurrent(pStr->GetString()),
			_widthPerFold(widthPerFold), _chPadding(chPadding) {}
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
	VType_String() : VType(serialId) {}
	explicit VType_String(const Symbol* pSymbol) : VType(serialId) {}
	explicit VType_String(const char* name) : VType(name, serialId) {}
	virtual void DoPrepare(Frame& frameOuter) override;
	virtual Value* DoCastFrom(Processor& processor, const Value& value, DeclArg::Flags flags) const override;
	virtual Value* DoDeserialize(Stream& stream) const override;
};

extern GURAX_DLLDECLARE VType_String VTYPE_String;

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
	static VType& vtype;
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
	static const char* ValueForVector(Value& value) { return GetString(value); }
public:
	// Virtual functions of Value
	virtual Value* Clone() const override { return Reference(); }
	virtual size_t DoCalcHash() const override {
		return String::CalcHash(GetString());
	}
	virtual bool IsEqualTo(const Value& value) const override {
		return IsSameType(value) &&
			String::IsEqualTo(GetString(), dynamic_cast<const Value_String&>(value).GetString());
	}
	virtual bool IsLessThan(const Value& value) const override {
		return IsSameType(value)?
			String::IsLessThan(GetString(), dynamic_cast<const Value_String&>(value).GetString()) :
			GetVTypeCustom().IsLessThan(value.GetVTypeCustom());
	}
	virtual String ToString(const StringStyle& ss) const override;
	virtual bool IsAsDictKey() const override { return true; }
	virtual bool Format_s(Formatter& formatter, FormatterFlags& formatterFlags) const override;
public:
	virtual bool DoEmptyIndexGet(Value** ppValue) const override;
	virtual bool DoEmptyIndexSet(RefPtr<Value> pValue) override;
	virtual bool DoSingleIndexGet(const Value& valueIndex, Value** ppValue) const override;
	virtual bool DoSingleIndexSet(Processor& processor, const Value& valueIndex, RefPtr<Value> pValue) override;
	virtual Iterator* DoGenIterator() const override;
	virtual bool DoSerialize(Stream& stream) const override;
};

//------------------------------------------------------------------------------
// VType_String::Iterator_Split
//------------------------------------------------------------------------------
template<typename T_CharCmp>
Value* VType_String::Iterator_Split<T_CharCmp>::DoNextValue()
{
	if (!*_pCurrent) {
		if (_foundFlag) {
			_foundFlag = false;
			return new Value_String("");
		}
		return nullptr;
	}
	if (_cnt == _cntMax) {
		RefPtr<Value> pValue(new Value_String(_pCurrent));
		_foundFlag = false;
		_pCurrent += ::strlen(_pCurrent);
		return pValue.release();
	}
	const char* pCurrentNext = _pCurrent;
	const char* pEnd = String::Find<T_CharCmp>(_pCurrent, _sep.c_str(), &pCurrentNext);
	String strRtn(_pCurrent, pEnd);
	_cnt++;
	_foundFlag = (*pEnd != '\0');
	_pCurrent = pCurrentNext;
	return new Value_String(strRtn);
}

template<typename T_CharCmp>
String VType_String::Iterator_Split<T_CharCmp>::ToString(const StringStyle& ss) const
{
	return "String#Split";
}

}

#endif
