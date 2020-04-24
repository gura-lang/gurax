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
	// Copy constructor/operator
	Tag(const Tag& src) = delete;
	Tag& operator=(const Tag& src) = delete;
	// Move constructor/operator
	Tag(Tag&& src) = delete;
	Tag& operator=(Tag&& src) noexcept = delete;
protected:
	~Tag() = default;
public:
	static Tag* Create(UInt typeId, UInt16 tagId, const Symbol* pSymbol,
										Value* pValue, Value* pValueCooked);
	static Tag* Create(UInt typeId, UInt16 tagId, const Symbol* pSymbol, Value* pValue) {
		return Create(typeId, tagId, pSymbol, pValue, pValue->Reference());
	}
public:
	UInt16 GetTagId() const { return _tagId; }
	UInt16 GetTypeId() const { return _typeId; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	const Value& GetValue() const { return *_pValue; }
	const Value& GetValueCooked() const { return *_pValueCooked; }
	void SetValue(Value* pValue) { _pValue.reset(pValue); }
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

class GURAX_DLLDECLARE Tag_BYTE : public Tag {
public:
	Tag_BYTE(UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked) :
		Tag(TypeId::BYTE, tagId, pSymbol, pValue, pValueCooked) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

class GURAX_DLLDECLARE Tag_ASCII : public Tag {
public:
	Tag_ASCII(UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked) :
		Tag(TypeId::ASCII, tagId, pSymbol, pValue, pValueCooked) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

class GURAX_DLLDECLARE Tag_SHORT : public Tag {
public:
	Tag_SHORT(UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked) :
		Tag(TypeId::SHORT, tagId, pSymbol, pValue, pValueCooked) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

class GURAX_DLLDECLARE Tag_LONG : public Tag {
public:
	Tag_LONG(UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked) :
		Tag(TypeId::LONG, tagId, pSymbol, pValue, pValueCooked) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

class GURAX_DLLDECLARE Tag_RATIONAL : public Tag {
public:
	Tag_RATIONAL(UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked) :
		Tag(TypeId::RATIONAL, tagId, pSymbol, pValue, pValueCooked) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

class GURAX_DLLDECLARE Tag_UNDEFINED : public Tag {
public:
	Tag_UNDEFINED(UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked) :
		Tag(TypeId::UNDEFINED, tagId, pSymbol, pValue, pValueCooked) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

class GURAX_DLLDECLARE Tag_SLONG : public Tag {
public:
	Tag_SLONG(UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked) :
		Tag(TypeId::SLONG, tagId, pSymbol, pValue, pValueCooked) {}
public:
	virtual bool CheckAcceptableValue(Value& value) const override;
	virtual bool WriteToStream(Stream& stream) const override;
};

class GURAX_DLLDECLARE Tag_SRATIONAL : public Tag {
public:
	Tag_SRATIONAL(UInt16 tagId, const Symbol* pSymbol, Value* pValue, Value* pValueCooked) :
		Tag(TypeId::SRATIONAL, tagId, pSymbol, pValue, pValueCooked) {}
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
