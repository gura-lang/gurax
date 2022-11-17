//==============================================================================
// Tag.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_TAG_H
#define GURAX_MODULE_JPEG_TAG_H
#include <gurax.h>
#include "Symbol.h"

Gurax_BeginModuleScope(jpeg)

class TagList;

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
			Assoc(Gurax_Symbol(BYTE),					TypeId::BYTE);
			Assoc(Gurax_Symbol(ASCII),					TypeId::ASCII);
			Assoc(Gurax_Symbol(SHORT),					TypeId::SHORT);
			Assoc(Gurax_Symbol(LONG),					TypeId::LONG);
			Assoc(Gurax_Symbol(RATIONAL),				TypeId::RATIONAL);
			Assoc(Gurax_Symbol(UNDEFINED),				TypeId::UNDEFINED);
			Assoc(Gurax_Symbol(SLONG),					TypeId::SLONG);
			Assoc(Gurax_Symbol(SRATIONAL),				TypeId::SRATIONAL);
			Assoc(Gurax_Symbol(JPEGInterchangeFormat),	TypeId::JPEGInterchangeFormat);
			Assoc(Gurax_Symbol(IFD),					TypeId::IFD);
		}
		static const SymbolAssoc& GetInstance() {
			static SymbolAssoc* pSymbolAssoc = nullptr;
			return pSymbolAssoc? *pSymbolAssoc : *(pSymbolAssoc = new SymbolAssoc_TypeId());
		}
	};
	struct GURAX_DLLDECLARE OrderHintCompare {
	public:
		bool operator()(const Tag* pTag1, const Tag* pTag2) const {
			return pTag1->GetOrderHint() < pTag2->GetOrderHint();
		}
	};
protected:
	UInt16 _tagId;
	UInt16 _typeId;
	const Symbol* _pSymbol;
	size_t _posPointer;
	UInt32 _orderHint;
	RefPtr<Value> _pValue;
	RefPtr<Value> _pValueCooked;
protected:
	// Constructor
	Tag(UInt16 tagId, UInt16 typeId, const Symbol* pSymbol);
	// Copy constructor/operator
	Tag(const Tag& src) = delete;
	Tag& operator=(const Tag& src) = delete;
	// Move constructor/operator
	Tag(Tag&& src) = delete;
	Tag& operator=(Tag&& src) noexcept = delete;
protected:
	~Tag() = default;
public:
	static Tag* Create(const Symbol* pSymbolOfIFD, const Symbol* pSymbol);
	static Tag* Create(UInt16 tagId, UInt16 typeId, const Symbol* pSymbol);
public:
	UInt16 GetTagId() const { return _tagId; }
	UInt16 GetTypeId() const { return _typeId; }
	UInt16 GetTypeIdRaw() const {
		return (_typeId == TypeId::JPEGInterchangeFormat || _typeId == TypeId::IFD)?
			TypeId::LONG : _typeId;
	}
	void SetOrderHintAsAdded() { _orderHint = 0xfffffff0; }
	UInt32 GetOrderHint() const { return _orderHint; }
	const Symbol* GetSymbol() const { return _pSymbol; }
	void SetValue(RefPtr<Value> pValue) {
		_pValue.reset(pValue.Reference());
		_pValueCooked.reset(pValue.release());
	}
	Value& GetValue() { return *_pValue; }
	const Value& GetValueCooked() const { return *_pValueCooked; }
	static size_t CalcPosPointer(const Binary& buff) { return buff.size() + 2 + 2 + 4; }
	static UInt32 CalcOffset(const Binary& buff) { return static_cast<UInt32>(buff.size()) - 6; }
	template<typename TypeDef> static void ReplaceLONG(Binary& buff, size_t pos, UInt32 num);
public:
	virtual VType& GetVTypeAcceptable() = 0;
	virtual bool AssignValue(RefPtr<Value> pValue) = 0;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) = 0;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) = 0;
	virtual bool SerializePointed(Binary& buff, bool beFlag) = 0;
protected:
	bool CheckRangedNumber(const Value& value, Double numMin, Double numMax) const;
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
	Gurax_PackUInt16(tagPacked.typeId, GetTypeIdRaw());
	Gurax_PackUInt32(tagPacked.count, count);
	return tagPacked;
}

template<typename TypeDef> void Tag::ReplaceLONG(Binary& buff, size_t pos, UInt32 num)
{
	TypeDef::LONG packed;
	Gurax_PackUInt32(packed.num, num);
	buff.replace(pos, sizeof(TypeDef::LONG),
		reinterpret_cast<UInt8*>(&packed), sizeof(TypeDef::LONG));
}

//------------------------------------------------------------------------------
// Tag_BYTE
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_BYTE : public Tag {
public:
	Tag_BYTE(UInt16 tagId, const Symbol* pSymbol) : Tag(tagId, TypeId::BYTE, pSymbol) {}
public:
	virtual VType& GetVTypeAcceptable() override;
	virtual bool AssignValue(RefPtr<Value> pValue) override;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) override;
	virtual bool SerializePointed(Binary& buff, bool beFlag) override;
protected:
	template<typename TypeDef> bool DoDeserialize(const UInt8* buff, size_t bytesBuff, size_t offset);
	template<typename TypeDef> bool DoSerialize(Binary& buff, TagList& tagsPointed);
	template<typename TypeDef> bool DoSerializePointed(Binary& buff);
};

//------------------------------------------------------------------------------
// Tag_ASCII
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_ASCII : public Tag {
public:
	Tag_ASCII(UInt16 tagId, const Symbol* pSymbol) : Tag(tagId, TypeId::ASCII, pSymbol) {}
public:
	virtual VType& GetVTypeAcceptable() override;
	virtual bool AssignValue(RefPtr<Value> pValue) override;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) override;
	virtual bool SerializePointed(Binary& buff, bool beFlag) override;
protected:
	template<typename TypeDef> bool DoDeserialize(const UInt8* buff, size_t bytesBuff, size_t offset);
	template<typename TypeDef> bool DoSerialize(Binary& buff, TagList& tagsPointed);
	template<typename TypeDef> bool DoSerializePointed(Binary& buff);
};

//------------------------------------------------------------------------------
// Tag_SHORT
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SHORT : public Tag {
public:
	Tag_SHORT(UInt16 tagId, const Symbol* pSymbol) : Tag(tagId, TypeId::SHORT, pSymbol) {}
public:
	virtual VType& GetVTypeAcceptable() override;
	virtual bool AssignValue(RefPtr<Value> pValue) override;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) override;
	virtual bool SerializePointed(Binary& buff, bool beFlag) override;
protected:
	template<typename TypeDef> bool DoDeserialize(const UInt8* buff, size_t bytesBuff, size_t offset);
	template<typename TypeDef> bool DoSerialize(Binary& buff, TagList& tagsPointed);
	template<typename TypeDef> bool DoSerializePointed(Binary& buff);
};

//------------------------------------------------------------------------------
// Tag_LONG
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_LONG : public Tag {
public:
	Tag_LONG(UInt16 tagId, const Symbol* pSymbol) : Tag(tagId, TypeId::LONG, pSymbol) {}
public:
	virtual VType& GetVTypeAcceptable() override;
	virtual bool AssignValue(RefPtr<Value> pValue) override;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) override;
	virtual bool SerializePointed(Binary& buff, bool beFlag) override;
protected:
	template<typename TypeDef> bool DoDeserialize(const UInt8* buff, size_t bytesBuff, size_t offset);
	template<typename TypeDef> bool DoSerialize(Binary& buff, TagList& tagsPointed);
	template<typename TypeDef> bool DoSerializePointed(Binary& buff);
};

//------------------------------------------------------------------------------
// Tag_RATIONAL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_RATIONAL : public Tag {
public:
	Tag_RATIONAL(UInt16 tagId, const Symbol* pSymbol) : Tag(tagId, TypeId::RATIONAL, pSymbol) {}
public:
	virtual VType& GetVTypeAcceptable() override;
	virtual bool AssignValue(RefPtr<Value> pValue) override;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) override;
	virtual bool SerializePointed(Binary& buff, bool beFlag) override;
protected:
	template<typename TypeDef> bool DoDeserialize(const UInt8* buff, size_t bytesBuff, size_t offset);
	template<typename TypeDef> bool DoSerialize(Binary& buff, TagList& tagsPointed);
	template<typename TypeDef> bool DoSerializePointed(Binary& buff);
};

//------------------------------------------------------------------------------
// Tag_UNDEFINED
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_UNDEFINED : public Tag {
public:
	Tag_UNDEFINED(UInt16 tagId, const Symbol* pSymbol) : Tag(tagId, TypeId::UNDEFINED, pSymbol) {}
public:
	virtual VType& GetVTypeAcceptable() override;
	virtual bool AssignValue(RefPtr<Value> pValue) override;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) override;
	virtual bool SerializePointed(Binary& buff, bool beFlag) override;
protected:
	template<typename TypeDef> bool DoDeserialize(const UInt8* buff, size_t bytesBuff, size_t offset);
	template<typename TypeDef> bool DoSerialize(Binary& buff, TagList& tagsPointed);
	template<typename TypeDef> bool DoSerializePointed(Binary& buff);
};

//------------------------------------------------------------------------------
// Tag_SLONG
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SLONG : public Tag {
public:
	Tag_SLONG(UInt16 tagId, const Symbol* pSymbol) : Tag(tagId, TypeId::SLONG, pSymbol) {}
public:
	virtual VType& GetVTypeAcceptable() override;
	virtual bool AssignValue(RefPtr<Value> pValue) override;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) override;
	virtual bool SerializePointed(Binary& buff, bool beFlag) override;
protected:
	template<typename TypeDef> bool DoDeserialize(const UInt8* buff, size_t bytesBuff, size_t offset);
	template<typename TypeDef> bool DoSerialize(Binary& buff, TagList& tagsPointed);
	template<typename TypeDef> bool DoSerializePointed(Binary& buff);
};

//------------------------------------------------------------------------------
// Tag_SRATIONAL
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_SRATIONAL : public Tag {
public:
	Tag_SRATIONAL(UInt16 tagId, const Symbol* pSymbol) : Tag(tagId, TypeId::SRATIONAL, pSymbol) {}
public:
	virtual VType& GetVTypeAcceptable() override;
	virtual bool AssignValue(RefPtr<Value> pValue) override;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) override;
	virtual bool SerializePointed(Binary& buff, bool beFlag) override;
protected:
	template<typename TypeDef> bool DoDeserialize(const UInt8* buff, size_t bytesBuff, size_t offset);
	template<typename TypeDef> bool DoSerialize(Binary& buff, TagList& tagsPointed);
	template<typename TypeDef> bool DoSerializePointed(Binary& buff);
};

//------------------------------------------------------------------------------
// Tag_IFD
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_IFD : public Tag {
public:
	Tag_IFD(UInt16 tagId, const Symbol* pSymbol) : Tag(tagId, TypeId::IFD, pSymbol) {}
public:
	virtual VType& GetVTypeAcceptable() override;
	virtual bool AssignValue(RefPtr<Value> pValue) override;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) override;
	virtual bool SerializePointed(Binary& buff, bool beFlag) override;
protected:
	template<typename TypeDef> bool DoDeserialize(const UInt8* buff, size_t bytesBuff, size_t offset);
	template<typename TypeDef> bool DoSerialize(Binary& buff, TagList& tagsPointed);
};

//------------------------------------------------------------------------------
// Tag_JPEGInterchangeFormat
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE Tag_JPEGInterchangeFormat : public Tag {
public:
	Tag_JPEGInterchangeFormat(const Symbol* pSymbol) :
			Tag(TagId::JPEGInterchangeFormat, TypeId::JPEGInterchangeFormat, pSymbol) {}
public:
	virtual VType& GetVTypeAcceptable() override;
	virtual bool AssignValue(RefPtr<Value> pValue) override;
	virtual bool Deserialize(const UInt8* buff, size_t bytesBuff, size_t offset, bool beFlag) override;
	virtual bool Serialize(Binary& buff, bool beFlag, TagList& tagsPointed) override;
	virtual bool SerializePointed(Binary& buff, bool beFlag) override;
protected:
	template<typename TypeDef> bool DoDeserialize(const UInt8* buff, size_t bytesBuff, size_t offset);
	template<typename TypeDef> bool DoSerialize(Binary& buff, TagList& tagsPointed);
	template<typename TypeDef> bool DoSerializePointed(Binary& buff);
};

//------------------------------------------------------------------------------
// TagList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE TagList : public ListBase<Tag*> {
public:
	void SortByOrderHint() { std::stable_sort(begin(), end(), Tag::OrderHintCompare()); }
	Tag* FindBySymbol(const Symbol* pSymbol);
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
	bool DeleteBySymbol(const Symbol* pSymbol);
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
	void Add(const Symbol* pSymbol, Tag* pTag);
	void Erase(const Symbol* pSymbol);
};

Gurax_EndModuleScope(jpeg)

#endif
