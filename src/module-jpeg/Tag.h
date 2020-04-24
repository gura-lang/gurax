//==============================================================================
// Tag.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_TAG_H
#define GURAX_MODULE_JPEG_TAG_H
#include <gurax.h>

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Tag
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(Tag);
protected:
	UInt16 _typeId;
	UInt16 _tagId;
	const Symbol* _pSymbol;
	RefPtr<Value> _pValue;
	RefPtr<Value> _pValueCooked;
protected:
	// Constructor
	Tag(UInt16 typeId, UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked);
	Tag(UInt16 typeId, UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(typeId, tagId, pSymbol, pValue, pValue->Reference()) {}
	Tag(UInt16 typeId, UInt16 tagId, const Symbol* pSymbol) :
		Tag(typeId, tagId, pSymbol, Value::nil(), Value::nil()) {}
	// Copy constructor/operator
	Tag(const Tag& src) = delete;
	Tag& operator=(const Tag& src) = delete;
	// Move constructor/operator
	Tag(Tag&& src) = delete;
	Tag& operator=(Tag&& src) noexcept = delete;
protected:
	~Tag() = default;
public:
	UInt16 GetTagId() const { return _tagId; }
	UInt16 GetTypeId() const { return _typeId; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Value& GetValue() const { return *_pValue; }
	const Value& GetValueCooked() const { return *_pValueCooked; }
	void SetValue(Value* pValue) {
		_pValue.reset(pValue); _pValueCooked.reset(pValue->Reference());
	}
public:
	virtual bool CheckAcceptableValue(Value& value) const = 0;
	virtual bool WriteToStream(Stream& stream) const = 0;
protected:
	static bool CheckRangedNumber(const Value& value, Double numMin, Double numMax);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const Tag& other) const { return this == &other; }
	bool IsEqualTo(const Tag& other) const { return IsIdentical(other); }
	bool IsLessThan(const Tag& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

//------------------------------------------------------------------------------
// Tag_BYTE
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_BYTE : public Tag {
public:
	Tag_BYTE(UInt16 tagId, const Symbol* pSymbol) : Tag(TypeId::BYTE, tagId, pSymbol) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

template<typename TypeDef> Tag* Tag_BYTE::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto &tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto &variable = tagPacked.variable;
	const UInt8* pBuff = variable.BYTE;
	if (count > 4) {
		size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
		if (offset + count * sizeof(UInt8) > bytesBuff) {
			IssueError_InvalidFormat();
			return nullptr;
		}
		pBuff = buff + offset;
	}
	SetValue(new Value_Binary(Binary(pBuff, count)));
	return this;
}

//------------------------------------------------------------------------------
// Tag_ASCII
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_ASCII : public Tag {
public:
	Tag_ASCII(UInt16 tagId, const Symbol* pSymbol) : Tag(TypeId::ASCII, tagId, pSymbol) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

template<typename TypeDef> Tag* Tag_ASCII::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto &tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto &variable = tagPacked.variable;
	const char* pBuff = variable.ASCII;
	if (count > 4) {
		size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
		if (offset + count * sizeof(char) > bytesBuff) {
			IssueError_InvalidFormat();
			return nullptr;
		}
		pBuff = reinterpret_cast<const char*>(buff + offset);
	}
	SetValue(new Value_String(String(pBuff, count)));
	return this;
}

//------------------------------------------------------------------------------
// Tag_SHORT
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SHORT : public Tag {
public:
	Tag_SHORT(UInt16 tagId, const Symbol* pSymbol) : Tag(TypeId::SHORT, tagId, pSymbol) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

template<typename TypeDef> Tag* Tag_SHORT::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using SHORT_T = typename TypeDef::SHORT;
	auto &tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto &variable = tagPacked.variable;
	if (count == 1) {
		UInt16 num = Gurax_UnpackUInt16(variable.SHORT.num);
		SetValue(new Value_Number(num));
	} else if (count == 2) {
		UInt16 num1 = Gurax_UnpackUInt16(variable.SHORT.num);
		UInt16 num2 = Gurax_UnpackUInt16(variable.SHORT.num2nd);
		SetValue(Value_List::Create(new Value_Number(num1), new Value_Number(num2)));
	} else {
		size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
		if (offset + count * sizeof(SHORT_T) > bytesBuff) {
			IssueError_InvalidFormat();
			return nullptr;
		}
		RefPtr<ValueOwner> pValueOwner(new ValueOwner());
		pValueOwner->reserve(count);
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
	Tag_LONG(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::LONG, tagId, pSymbol, pValue) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

template<typename TypeDef> Tag* Tag_LONG::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto &tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto &variable = tagPacked.variable;

	return this;
}

//------------------------------------------------------------------------------
// Tag_RATIONAL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_RATIONAL : public Tag {
public:
	Tag_RATIONAL(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::RATIONAL, tagId, pSymbol, pValue) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

template<typename TypeDef> Tag* Tag_RATIONAL::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto &tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto &variable = tagPacked.variable;

	return this;
}

//------------------------------------------------------------------------------
// Tag_UNDEFINED
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_UNDEFINED : public Tag {
public:
	Tag_UNDEFINED(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::UNDEFINED, tagId, pSymbol, pValue) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

template<typename TypeDef> Tag* Tag_UNDEFINED::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto &tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto &variable = tagPacked.variable;

	return this;
}

//------------------------------------------------------------------------------
// Tag_SLONG
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SLONG : public Tag {
public:
	Tag_SLONG(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::SLONG, tagId, pSymbol, pValue) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

template<typename TypeDef> Tag* Tag_SLONG::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto &tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto &variable = tagPacked.variable;

	return this;
}

//------------------------------------------------------------------------------
// Tag_SRATIONAL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SRATIONAL : public Tag {
public:
	Tag_SRATIONAL(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::SRATIONAL, tagId, pSymbol, pValue) {}
public:
	template<typename TypeDef> inline Tag* ReadFromBuff(
		const UInt8* buff, size_t bytesBuff, size_t offset);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

template<typename TypeDef> Tag* Tag_SRATIONAL::ReadFromBuff(
	const UInt8* buff, size_t bytesBuff, size_t offset)
{
	auto &tagPacked = *reinterpret_cast<const typename TypeDef::TagPacked*>(buff + offset);
	UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
	auto &variable = tagPacked.variable;

	return this;
}

//------------------------------------------------------------------------------
// Tag_IFD
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_IFD : public Tag {
public:
	Tag_IFD(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::SRATIONAL, tagId, pSymbol, pValue) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
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
