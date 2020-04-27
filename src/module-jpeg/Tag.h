//==============================================================================
// Tag.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_TAG_H
#define GURAX_MODULE_JPEG_TAG_H
#include <gurax.h>
#include "Symbol.h"

Gurax_BeginModuleScope(jpeg)

class IFD;

//------------------------------------------------------------------------------
// SerialBuff
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE SerialBuff {
public:
	// Constructor
	SerialBuff() {}
	// Copy constructor/operator
	SerialBuff(const SerialBuff& src) = delete;
	SerialBuff& operator=(const SerialBuff& src) = delete;
	// Move constructor/operator
	SerialBuff(SerialBuff&& src) = delete;
	SerialBuff& operator=(SerialBuff&& src) noexcept = delete;
public:
	~SerialBuff() = default;
protected:
	Binary _buff;
	Binary _buffData;
public:
	Binary& GetBuff() { return _buff; }
	Binary& GetBuffData_BYTE() { return _buffData; }
	Binary& GetBuffData_ASCII() { return _buffData; }
	Binary& GetBuffData_SHORT() { return _buffData; }
	Binary& GetBuffData_LONG() { return _buffData; }
	Binary& GetBuffData_RATIONAL() { return _buffData; }
	Binary& GetBuffData_UNDEFINED() { return _buffData; }
	Binary& GetBuffData_SLONG() { return _buffData; }
	Binary& GetBuffData_SRATIONAL() { return _buffData; }
	size_t CalcOffsetToValue(size_t offsetToData) {
		return offsetToData + _buffData.size();
	}
public:
	bool WriteToBinary(Binary& buff);
};

//------------------------------------------------------------------------------
// Tag
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Tag);
public:
	class GURAX_DLLDECLARE SymbolAssoc_TypeId : public SymbolAssoc<UInt16, TypeId::None> {
	public:
		SymbolAssoc_TypeId() {
			Assoc(Gurax_Symbol(BYTE),		TypeId::BYTE);
			Assoc(Gurax_Symbol(ASCII),		TypeId::ASCII);
			Assoc(Gurax_Symbol(SHORT),		TypeId::SHORT);
			Assoc(Gurax_Symbol(LONG),		TypeId::LONG);
			Assoc(Gurax_Symbol(RATIONAL),	TypeId::RATIONAL);
			Assoc(Gurax_Symbol(UNDEFINED),	TypeId::UNDEFINED);
			Assoc(Gurax_Symbol(SLONG),		TypeId::SLONG);
			Assoc(Gurax_Symbol(SRATIONAL),	TypeId::SRATIONAL);
			Assoc(Gurax_Symbol(IFD),		TypeId::IFD);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_TypeId());
		}
	};
protected:
	UInt16 _typeId;
	UInt16 _tagId;
	const Symbol* _pSymbol;
	size_t _offset;
	size_t _offsetToValue;
	RefPtr<Value> _pValue;
	RefPtr<Value> _pValueCooked;
protected:
	// Constructor
	Tag(UInt16 typeId, UInt16 tagId, const Symbol* pSymbol,
		size_t offset, size_t offsetToValue, Value* pValue, Value* pValueCooked);
	Tag(UInt16 typeId, UInt16 tagId, const Symbol* pSymbol,
		size_t offset, size_t offsetToValue, Value* pValue) :
		Tag(typeId, tagId, pSymbol, offset, offsetToValue, pValue, pValue->Reference()) {}
	Tag(UInt16 typeId, UInt16 tagId, const Symbol* pSymbol, size_t offset, Value* pValue) :
		Tag(typeId, tagId, pSymbol, offset, offset, pValue, pValue->Reference()) {}
	Tag(UInt16 typeId, UInt16 tagId, const Symbol* pSymbol, size_t offset) :
		Tag(typeId, tagId, pSymbol, offset, offset, Value::nil(), Value::nil()) {}
	// Copy constructor/operator
	Tag(const Tag& src) = delete;
	Tag& operator=(const Tag& src) = delete;
	// Move constructor/operator
	Tag(Tag&& src) = delete;
	Tag& operator=(Tag&& src) noexcept = delete;
protected:
	~Tag() = default;
public:
	void ClearOffset() { _offset = _offsetToValue = 0; }
	UInt16 GetTagId() const { return _tagId; }
	UInt16 GetTypeId() const { return _typeId; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	size_t GetOffset() const { return _offset; }
	size_t GetOffsetToValue() const { return _offsetToValue; }
	const Value& GetValue() const { return *_pValue; }
	const Value& GetValueCooked() const { return *_pValueCooked; }
	void SetValue(Value* pValue) {
		_pValue.reset(pValue); _pValueCooked.reset(pValue->Reference());
	}
public:
	virtual bool CheckAcceptableValue(Value& value) const = 0;
	virtual bool SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag) = 0;
	virtual bool Serialize(SerialBuff& serialBuff, size_t offset, bool beFlag) const = 0;
protected:
	static bool CheckRangedNumber(const Value& value, Double numMin, Double numMax);
public:
	static UInt16 SymbolToTypeId(const Symbol* pSymbol) {
		return SymbolAssoc_TypeId::GetInstance().ToAssociated(pSymbol);
	}
	static const Symbol* TypeIdToSymbol(UInt16 typeId) {
		return SymbolAssoc_TypeId::GetInstance().ToSymbol(typeId);
	}
public:
	template<typename TypeDef> inline typename TypeDef::TagPacked MakeTagPacked(UInt32 count) const;
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Tag& other) const { return this == &other; }
	bool IsEqualTo(const Tag& other) const { return IsIdentical(other); }
	bool IsLessThan(const Tag& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

template<typename TypeDef> typename TypeDef::TagPacked Tag::MakeTagPacked(UInt32 count) const
{
	typename TypeDef::TagPacked tagPacked = { 0 };
	Gurax_PackUInt16(tagPacked.tagId, _tagId);
	Gurax_PackUInt16(tagPacked.typeId, _typeId);
	Gurax_PackUInt32(tagPacked.count, count);
	return tagPacked;
}

//------------------------------------------------------------------------------
// Tag_BYTE
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_BYTE : public Tag {
public:
	Tag_BYTE(UInt16 tagId, const Symbol* pSymbol, size_t offset) : Tag(TypeId::BYTE, tagId, pSymbol, offset) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(SerialBuff& serialBuff, size_t offset, bool beFlag) const override;
protected:
	template<typename TypeDef> bool DoSerializePre(SerialBuff& serialBuff, size_t offsetToData);
	template<typename TypeDef> bool DoSerialize(SerialBuff& serialBuff, size_t offset) const;
};

template<typename TypeDef> Tag* Tag_BYTE::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	const UInt8* pBuff = variable.BYTE;
	if (count > 4) {
		_offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		if (_offsetToValue + count * sizeof(UInt8) > bytesBuff) {
			IssueError_InvalidFormat();
			return nullptr;
		}
		pBuff = buff + _offsetToValue;
	}
	SetValue(new Value_Binary(Binary(pBuff, count)));
	return this;
}

//------------------------------------------------------------------------------
// Tag_ASCII
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_ASCII : public Tag {
public:
	Tag_ASCII(UInt16 tagId, const Symbol* pSymbol, size_t offset) : Tag(TypeId::ASCII, tagId, pSymbol, offset) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(SerialBuff& serialBuff, size_t offset, bool beFlag) const override;
protected:
	template<typename TypeDef> bool DoSerializePre(SerialBuff& serialBuff, size_t offsetToData);
	template<typename TypeDef> bool DoSerialize(SerialBuff& serialBuff, size_t offset) const;
};

template<typename TypeDef> Tag* Tag_ASCII::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	const char* pBuff = variable.ASCII;
	if (count > 4) {
		_offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		if (_offsetToValue + count * sizeof(char) > bytesBuff) {
			IssueError_InvalidFormat();
			return nullptr;
		}
		pBuff = reinterpret_cast<const char*>(buff + _offsetToValue);
	}
	SetValue(new Value_String(String(pBuff, count)));
	return this;
}

//------------------------------------------------------------------------------
// Tag_SHORT
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SHORT : public Tag {
public:
	Tag_SHORT(UInt16 tagId, const Symbol* pSymbol, size_t offset) : Tag(TypeId::SHORT, tagId, pSymbol, offset) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(SerialBuff& serialBuff, size_t offset, bool beFlag) const override;
protected:
	template<typename TypeDef> bool DoSerializePre(SerialBuff& serialBuff, size_t offsetToData);
	template<typename TypeDef> bool DoSerialize(SerialBuff& serialBuff, size_t offset) const;
};

template<typename TypeDef> Tag* Tag_SHORT::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using SHORT_T = typename TypeDef::SHORT;
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	if (count == 1) {
		UInt16 num = Gurax_UnpackUInt16(variable.SHORT.num);
		SetValue(new Value_Number(num));
	} else if (count == 2) {
		UInt16 num1 = Gurax_UnpackUInt16(variable.SHORT.num);
		UInt16 num2 = Gurax_UnpackUInt16(variable.SHORT.num2nd);
		SetValue(Value_List::Create(new Value_Number(num1), new Value_Number(num2)));
	} else {
		_offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		if (_offsetToValue + count * sizeof(SHORT_T) > bytesBuff) {
			IssueError_InvalidFormat();
			return nullptr;
		}
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
		size_t offset = _offsetToValue;
		for (size_t i = 0; i < count; i++, offset += sizeof(SHORT_T)) {
			const SHORT_T* pSHORT = reinterpret_cast<const SHORT_T*>(buff + offset);
			UInt16 num = Gurax_UnpackUInt16(pSHORT->num);
			pValueOwner->push_back(new Value_Number(num));
		}
		SetValue(new Value_List(VTYPE_Number, pValueOwner.release()));
	}
	return this;
}

//------------------------------------------------------------------------------
// Tag_LONG
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_LONG : public Tag {
public:
	Tag_LONG(UInt16 tagId, const Symbol* pSymbol, size_t offset) : Tag(TypeId::LONG, tagId, pSymbol, offset) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(SerialBuff& serialBuff, size_t offset, bool beFlag) const override;
protected:
	template<typename TypeDef> bool DoSerializePre(SerialBuff& serialBuff, size_t offsetToData);
	template<typename TypeDef> bool DoSerialize(SerialBuff& serialBuff, size_t offset) const;
};

template<typename TypeDef> Tag* Tag_LONG::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using LONG_T = typename TypeDef::LONG;
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	if (count == 1) {
		UInt32 num = Gurax_UnpackUInt32(variable.LONG.num);
		SetValue(new Value_Number(num));
	} else {
		_offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		if (_offsetToValue + count * sizeof(LONG_T) > bytesBuff) {
			IssueError_InvalidFormat();
			return nullptr;
		}
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
		size_t offset = _offsetToValue;
		for (size_t i = 0; i < count; i++, offset += sizeof(LONG_T)) {
			const LONG_T* pLONG = reinterpret_cast<const LONG_T*>(buff + offset);
			UInt32 num = Gurax_UnpackUInt32(pLONG->num);
			pValueOwner->push_back(new Value_Number(num));
		}
		SetValue(new Value_List(VTYPE_Number, pValueOwner.release()));
	}
	return this;
}

//------------------------------------------------------------------------------
// Tag_RATIONAL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_RATIONAL : public Tag {
public:
	Tag_RATIONAL(UInt16 tagId, const Symbol* pSymbol, size_t offset) : Tag(TypeId::RATIONAL, tagId, pSymbol, offset) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(SerialBuff& serialBuff, size_t offset, bool beFlag) const override;
protected:
	template<typename TypeDef> bool DoSerializePre(SerialBuff& serialBuff, size_t offsetToData);
	template<typename TypeDef> bool DoSerialize(SerialBuff& serialBuff, size_t offset) const;
};

template<typename TypeDef> Tag* Tag_RATIONAL::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using RATIONAL_T = typename TypeDef::RATIONAL;
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	_offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
	if (_offsetToValue + count * sizeof(RATIONAL_T) > bytesBuff) {
		IssueError_InvalidFormat();
		return nullptr;
	}
	if (count == 1) {
		const RATIONAL_T* pRATIONAL = reinterpret_cast<const RATIONAL_T*>(buff + _offsetToValue);
		RefPtr<Value> pValue(CreateValueFromRATIONAL(*pRATIONAL));
		if (!pValue) return nullptr;
		SetValue(pValue.release());
	} else {
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
		size_t offset = _offsetToValue;
		for (size_t i = 0; i < count; i++, offset += sizeof(RATIONAL_T)) {
			const RATIONAL_T* pRATIONAL = reinterpret_cast<const RATIONAL_T*>(buff + offset);
			RefPtr<Value> pValueElem(CreateValueFromRATIONAL(*pRATIONAL));
			if (!pValueElem) return nullptr;
			pValueOwner->push_back(pValueElem.release());
		}
		SetValue(new Value_List(VTYPE_Number, pValueOwner.release()));
	}
	return this;
}

//------------------------------------------------------------------------------
// Tag_UNDEFINED
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_UNDEFINED : public Tag {
public:
	Tag_UNDEFINED(UInt16 tagId, const Symbol* pSymbol, size_t offset) : Tag(TypeId::UNDEFINED, tagId, pSymbol, offset) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(SerialBuff& serialBuff, size_t offset, bool beFlag) const override;
protected:
	template<typename TypeDef> bool DoSerializePre(SerialBuff& serialBuff, size_t offsetToData);
	template<typename TypeDef> bool DoSerialize(SerialBuff& serialBuff, size_t offset) const;
};

template<typename TypeDef> Tag* Tag_UNDEFINED::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	const UInt8* pBuff = variable.BYTE;
	if (count > 4) {
		_offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		if (_offsetToValue + count * sizeof(UInt8) > bytesBuff) {
			IssueError_InvalidFormat();
			return nullptr;
		}
		pBuff = buff + _offsetToValue;
	}
	SetValue(new Value_Binary(Binary(pBuff, count)));
	return this;
}

//------------------------------------------------------------------------------
// Tag_SLONG
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SLONG : public Tag {
public:
	Tag_SLONG(UInt16 tagId, const Symbol* pSymbol, size_t offset) : Tag(TypeId::SLONG, tagId, pSymbol, offset) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(SerialBuff& serialBuff, size_t offset, bool beFlag) const override;
protected:
	template<typename TypeDef> bool DoSerializePre(SerialBuff& serialBuff, size_t offsetToData);
	template<typename TypeDef> bool DoSerialize(SerialBuff& serialBuff, size_t offset) const;
};

template<typename TypeDef> Tag* Tag_SLONG::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using SLONG_T = typename TypeDef::SLONG;
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	if (count == 1) {
		Int32 num = Gurax_UnpackInt32(variable.SLONG.num);
		SetValue(new Value_Number(num));
	} else {
		_offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
		if (_offsetToValue + count * sizeof(SLONG_T) > bytesBuff) {
			IssueError_InvalidFormat();
			return nullptr;
		}
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
		size_t offset = _offsetToValue;
		for (size_t i = 0; i < count; i++, offset += sizeof(SLONG_T)) {
			const SLONG_T* pSLONG = reinterpret_cast<const SLONG_T*>(buff + offset);
			Int32 num = Gurax_UnpackInt32(pSLONG->num);
			pValueOwner->push_back(new Value_Number(num));
		}
		SetValue(new Value_List(VTYPE_Number, pValueOwner.release()));
	}
	return this;
}

//------------------------------------------------------------------------------
// Tag_SRATIONAL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SRATIONAL : public Tag {
public:
	Tag_SRATIONAL(UInt16 tagId, const Symbol* pSymbol, size_t offset) : Tag(TypeId::SRATIONAL, tagId, pSymbol, offset) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(SerialBuff& serialBuff, size_t offset, bool beFlag) const override;
protected:
	template<typename TypeDef> bool DoSerializePre(SerialBuff& serialBuff, size_t offsetToData);
	template<typename TypeDef> bool DoSerialize(SerialBuff& serialBuff, size_t offset) const;
};

template<typename TypeDef> Tag* Tag_SRATIONAL::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using SRATIONAL_T = typename TypeDef::SRATIONAL;
	auto& tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto& variable = tagPacked.variable;
	_offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
	if (_offsetToValue + count * sizeof(SRATIONAL_T) > bytesBuff) {
		IssueError_InvalidFormat();
		return nullptr;
	}
	if (count == 1) {
		const SRATIONAL_T* pSRATIONAL = reinterpret_cast<const SRATIONAL_T*>(buff + _offsetToValue);
		RefPtr<Value> pValue(CreateValueFromSRATIONAL(*pSRATIONAL));
		if (!pValue) return nullptr;
		SetValue(pValue.release());
	} else {
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
		size_t offset = _offsetToValue;
		for (size_t i = 0; i < count; i++, offset += sizeof(SRATIONAL_T)) {
			const SRATIONAL_T* pSRATIONAL = reinterpret_cast<const SRATIONAL_T*>(buff + offset);
			RefPtr<Value> pValueElem(CreateValueFromSRATIONAL(*pSRATIONAL));
			if (!pValueElem) return nullptr;
			pValueOwner->push_back(pValueElem.release());
		}
		SetValue(new Value_List(VTYPE_Number, pValueOwner.release()));
	}
	return this;
}

//------------------------------------------------------------------------------
// Tag_IFD
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_IFD : public Tag {
public:
	Tag_IFD(UInt16 tagId, const Symbol* pSymbol, size_t offset, size_t offsetToValue, Value* pValue) :
		Tag(TypeId::IFD, tagId, pSymbol, offset, pValue) { _offsetToValue = offsetToValue; }
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool SerializePre(SerialBuff& serialBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(SerialBuff& serialBuff, size_t offset, bool beFlag) const override;
protected:
	template<typename TypeDef> bool DoSerializePre(SerialBuff& serialBuff, size_t offsetToData);
	template<typename TypeDef> bool DoSerialize(SerialBuff& serialBuff, size_t offset) const;
};

//------------------------------------------------------------------------------
// TagList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TagList : public std::vector<Tag*> {
};

//------------------------------------------------------------------------------
// TagOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TagOwner : public TagList, public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(TagOwner);
protected:
	~TagOwner() { Clear(); }
public:
	void Clear();
};

//------------------------------------------------------------------------------
// TagMap
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TagMap :
	 public std::unordered_map<const Symbol*, Tag*, Symbol::Hash_UniqId, Symbol::EqualTo_UniqId> {
public:
	~TagMap() { Clear(); }
	void Clear();
	Tag* Lookup(const Symbol* pSymbol) const;
};

Gurax_EndModuleScope(jpeg)

#endif
