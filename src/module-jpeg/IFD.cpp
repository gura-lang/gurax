//==============================================================================
// IFD.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// IFD
//------------------------------------------------------------------------------
bool IFD::Serialize(Binary& buff, bool beFlag)
{
	UInt16 tagCount = static_cast<UInt16>(GetTagOwner().size());
	if (beFlag) {
		TypeDef_BE::IFDHeader hdr;
		Gurax_PackUInt16(hdr.tagCount, tagCount);
		buff.Append(&hdr, sizeof(hdr));
	} else {
		TypeDef_LE::IFDHeader hdr;
		Gurax_PackUInt16(hdr.tagCount, tagCount);
		buff.Append(&hdr, sizeof(hdr));
	}
	TagList tagsPointed;
	for (Tag* pTag : GetTagOwner()) {
		if (!pTag->Serialize(buff, beFlag, tagsPointed)) return false;
	}
	_posNextIFDOffset = buff.size();
	buff.Append("\0\0\0\0", 4);	// place holder for offsetNextIFD
	tagsPointed.SortByOrderHint();
	for (Tag* pTag : tagsPointed) {
		if (!pTag->SerializePointed(buff, beFlag)) return false;
	}
	return true;
}

void IFD::PrepareTagMap()
{
	for (const Tag* pTag : GetTagOwner()) {
		_tagMap[pTag->GetSymbol()] = pTag->Reference();
	}
}

void IFD::AddTag(Tag* pTag)
{
	GetTagOwner().push_back(pTag->Reference());
	GetTagMap().Add(pTag->GetSymbol(), pTag);
}

void IFD::DeleteTag(const Symbol* pSymbol)
{
	GetTagOwner().Erase(pSymbol);
	GetTagMap().Erase(pSymbol);
}

const Value* IFD::GetTagValue(const Symbol* pSymbol)
{
	Tag* pTag = GetTagMap().Lookup(pSymbol);
	return pTag? pTag->GetValue().Reference() : nullptr;
}

bool IFD::SetTagValue(const Symbol* pSymbol, RefPtr<Value> pValue)
{
	Tag* pTag = GetTagMap().Lookup(pSymbol);
	if (!pTag) {
		if (pValue->IsNil()) return true;
		const TagInfo* pTagInfo = TagInfo::LookupBySymbol(_pSymbolOfIFD, pSymbol);
		if (!pTagInfo) return false;
		RefPtr<Tag> pTag(Tag::Create(pTagInfo->tagId, pTagInfo->typeId, pTagInfo));
		if (!pTag) return false;
		pTag->SetOrderHintAsAdded();
		if (!pTag->CheckAcceptableValue(*pValue)) return false;
		pTag->SetValue(pValue.release());
		AddTag(pTag.release());
	} else if (pValue->IsNil()) {
		DeleteTag(pSymbol);
	} else {
		if (!pTag->CheckAcceptableValue(*pValue)) return false;
		pTag->SetValue(pValue.release());
	}
	return true;
}

String IFD::ToString(const StringStyle& ss) const
{
	return "jpeg.IFD";
}

//------------------------------------------------------------------------------
// IFDList
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// IFDOwner
//------------------------------------------------------------------------------
void IFDOwner::Clear()
{
	for (IFD* pIFD : *this) IFD::Delete(pIFD);
	clear();
}

Gurax_EndModuleScope(jpeg)
