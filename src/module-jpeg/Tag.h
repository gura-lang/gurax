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
	template<typename TypeDef> inline Tag* StoreVariable(
		UInt32 count, const typename TypeDef::Variable& variable,
		const UInt8* buff, size_t bytesBuff);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

template<typename TypeDef> Tag* Tag_BYTE::StoreVariable(
	UInt32 count, const typename TypeDef::Variable& variable,
	const UInt8* buff, size_t bytesBuff)
{
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
	template<typename TypeDef> inline Tag* StoreVariable(
		UInt32 count, const typename TypeDef::Variable& variable,
		const UInt8* buff, size_t bytesBuff);
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

template<typename TypeDef> Tag* Tag_ASCII::StoreVariable(
	UInt32 count, const typename TypeDef::Variable& variable,
	const UInt8* buff, size_t bytesBuff)
{
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
	Tag_SHORT(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::SHORT, tagId, pSymbol, pValue) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

//------------------------------------------------------------------------------
// Tag_LONG
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_LONG : public Tag {
public:
	Tag_LONG(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::LONG, tagId, pSymbol, pValue) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

//------------------------------------------------------------------------------
// Tag_RATIONAL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_RATIONAL : public Tag {
public:
	Tag_RATIONAL(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::RATIONAL, tagId, pSymbol, pValue) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

//------------------------------------------------------------------------------
// Tag_UNDEFINED
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_UNDEFINED : public Tag {
public:
	Tag_UNDEFINED(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::UNDEFINED, tagId, pSymbol, pValue) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

//------------------------------------------------------------------------------
// Tag_SLONG
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SLONG : public Tag {
public:
	Tag_SLONG(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::SLONG, tagId, pSymbol, pValue) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

//------------------------------------------------------------------------------
// Tag_SRATIONAL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SRATIONAL : public Tag {
public:
	Tag_SRATIONAL(UInt16 tagId, const Symbol* pSymbol, Value* pValue) :
		Tag(TypeId::SRATIONAL, tagId, pSymbol, pValue) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

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
