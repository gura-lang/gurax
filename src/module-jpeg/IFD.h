//==============================================================================
// IFD.h
//==============================================================================
#ifndef GURAX_MODULE_JPEG_IFD_H
#define GURAX_MODULE_JPEG_IFD_H
#include <gurax.h>
#include "Tag.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// IFD
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IFD : public Referable {
public:
	// Referable declaration
	Gurax_DeclareReferable(IFD);
protected:
	const Symbol* _pSymbolOfIFD;
	RefPtr<TagOwner> _pTagOwner;
	TagMap _tagMap;
	size_t _posNextIFDOffset;
public:
	// Constructor
	IFD(const Symbol* pSymbolOfIFD, TagOwner* pTagOwner) :
				_pSymbolOfIFD(pSymbolOfIFD), _pTagOwner(pTagOwner), _posNextIFDOffset(0) {
		PrepareTagMap();
	}
	// Copy constructor/operator
	IFD(const IFD& src) = delete;
	IFD& operator=(const IFD& src) = delete;
	// Move constructor/operator
	IFD(IFD&& src) = delete;
	IFD& operator=(IFD&& src) noexcept = delete;
protected:
	~IFD() = default;
public:
	static IFD* CreateFromList(const Symbol* pSymbolOfIFD, const ValueList& valueList);
	void SetSymbolOfIFD(const Symbol* pSymbol) {
		if (_pSymbolOfIFD->IsEmpty()) _pSymbolOfIFD = pSymbol;
	}
	const Symbol* GetSymbolOfIFD() const { return _pSymbolOfIFD; }
	TagOwner& GetTagOwner() { return *_pTagOwner; }
	const TagOwner& GetTagOwner() const { return *_pTagOwner; }
	TagMap& GetTagMap() { return _tagMap; }
	const TagMap& GetTagMap() const { return _tagMap; }
	size_t GetPosNextIFDOffset() { return _posNextIFDOffset; }
public:
	void PrepareTagMap();
	bool Serialize(Binary& buff, bool beFlag);
	void AddTag(Tag* pTag);
	Tag* CreateTag(const Symbol* pSymbol);
	void DeleteTag(const Symbol* pSymbol);
	bool AssignTagValue(const Symbol* pSymbol, RefPtr<Value> pValue);
public:
	template<typename TypeDef> static IFD* Deserialize(const UInt8* buff,
			size_t bytesBuff, size_t offset, const Symbol* pSymbolOfIFD,
			size_t* pOffsetNext = nullptr);
public:
	size_t CalcHash() const { return reinterpret_cast<size_t>(this); }
	bool IsIdentical(const IFD& other) const { return this == &other; }
	bool IsEqualTo(const IFD& other) const { return IsIdentical(other); }
	bool IsLessThan(const IFD& other) const { return this < &other; }
	String ToString(const StringStyle& ss = StringStyle::Empty) const;
};

template<typename TypeDef> IFD* IFD::Deserialize(const UInt8* buff, size_t bytesBuff,
	size_t offset, const Symbol* pSymbolOfIFD, size_t* pOffsetNext)
{
	using IFDHeader_T	= typename TypeDef::IFDHeader;
	using LONG_T		= typename TypeDef::LONG;
	using TagPacked_T	= typename TypeDef::TagPacked;
	if (pOffsetNext) *pOffsetNext = 0;
	if (offset + sizeof(IFDHeader_T) > bytesBuff) {
		IssueError_InvalidFormat();
		return nullptr;
	}
	RefPtr<TagOwner> pTagOwner(new TagOwner());
	auto& hdr = *reinterpret_cast<const IFDHeader_T*>(buff + offset);
	size_t tagCount = Gurax_UnpackUInt16(hdr.tagCount);
	offset += sizeof(IFDHeader_T);
	if (offset + sizeof(TagPacked_T) * tagCount + sizeof(LONG_T) > bytesBuff) {
		IssueError_InvalidFormat();
		return nullptr;
	}
	for (size_t iTag = 0; iTag < tagCount; iTag++, offset += sizeof(TagPacked_T)) {
		auto &tagPacked = *reinterpret_cast<const TagPacked_T*>(buff + offset);
		UInt16 tagId = Gurax_UnpackUInt16(tagPacked.tagId);
		UInt16 typeId = Gurax_UnpackUInt16(tagPacked.typeId);
		const TagInfo* pTagInfo = TagInfo::LookupByTagId(pSymbolOfIFD, tagId);
		const Symbol* pSymbol = nullptr;
		if (pTagInfo) {
			typeId = pTagInfo->typeId;
			pSymbol = Symbol::Add(pTagInfo->name);
		} else {
			pSymbol = Symbol::Add(String().Format("Tag%04x", tagId));
		}
		RefPtr<Tag> pTag(Tag::Create(tagId, typeId, pSymbol));
		if (!pTag || !pTag->Deserialize(buff, bytesBuff, offset, TypeDef::beFlag)) return nullptr;
		pTagOwner->push_back(pTag.release());
	}
	if (pOffsetNext) {
		const LONG_T* pLONG = reinterpret_cast<const LONG_T*>(buff + offset);
		*pOffsetNext = Gurax_UnpackUInt32(pLONG->num);
	}
	return new IFD(pSymbolOfIFD, pTagOwner.release());
}

//------------------------------------------------------------------------------
// IFDList
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IFDList : public ListBase<IFD*> {
};

//------------------------------------------------------------------------------
// IFDOwner
//------------------------------------------------------------------------------
class GURAX_DLLDECLARE IFDOwner : public IFDList {
public:
	~IFDOwner() { Clear(); }
	void Clear();
};

Gurax_EndModuleScope(jpeg)

#endif
