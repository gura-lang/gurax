//==============================================================================
// IFD.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// IFD
//------------------------------------------------------------------------------
IFD* IFD::CreateFromList(const Symbol* pSymbolOfIFD, const ValueList& valueList)
{
	RefPtr<TagOwner> pTagOwner(new TagOwner());
	for (const Value* pValueElem : valueList) {
		const ValueOwner* pValueOwner;
		if (pValueElem->IsList()) {
			pValueOwner = &Value_List::GetValueOwner(*pValueElem);
		} else if (pValueElem->IsTuple()) {
			pValueOwner = &Value_Tuple::GetValueOwner(*pValueElem);
		} else {
			Error::Issue(ErrorType::FormatError, "each element must be a List or Tuple");
			return false;
		}
		if (pValueOwner->size() != 2) {
			Error::Issue(ErrorType::FormatError, "each element of IFD value must be a key-value pair");
			return false;
		}
		if (!pValueOwner->front()->IsType(VTYPE_Expr)) {
			Error::Issue(ErrorType::FormatError, "each element of IFD value must has a symbol as its first value");
			return false;
		}
		const Symbol* pSymbol = Value_Expr::GetExpr(*pValueOwner->front()).GetPureSymbol();
		if (!pSymbol) {
			Error::Issue(ErrorType::FormatError, "each element of IFD value must has a symbol as its first value");
			return false;
		}
		Value& valueToAssign = *pValueOwner->back();
		RefPtr<Tag> pTag(Tag::Create(pSymbolOfIFD, pSymbol));
		if (!pTag) return false;
		if (!pTag->AssignValue(valueToAssign.Reference())) return false;
		pTagOwner->push_back(pTag.release());
	}
	return new IFD(pSymbolOfIFD, pTagOwner.release());
}

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

Tag* IFD::CreateTag(const Symbol* pSymbol)
{
	Tag* pTag = GetTagMap().Lookup(pSymbol);
	if (!pTag) {
		pTag = Tag::Create(_pSymbolOfIFD, pSymbol);
		if (!pTag) return nullptr;
		pTag->SetOrderHintAsAdded();
		AddTag(pTag);
	}
	return pTag->Reference();
}

void IFD::DeleteTag(const Symbol* pSymbol)
{
	GetTagOwner().DeleteBySymbol(pSymbol);
	GetTagMap().Erase(pSymbol);
}

bool IFD::AssignTagValue(const Symbol* pSymbol, RefPtr<Value> pValue)
{
	if (pValue->IsType(VTYPE_IFD)) Value_IFD::GetIFD(*pValue).SetSymbolOfIFD(pSymbol);
	Tag* pTag = GetTagMap().Lookup(pSymbol);
	if (!pTag) {
		if (pValue->IsNil()) return true;
		RefPtr<Tag> pTag(Tag::Create(_pSymbolOfIFD, pSymbol));
		if (!pTag) return false;
		pTag->SetOrderHintAsAdded();
		if (!pTag->AssignValue(pValue.release())) return false;
		AddTag(pTag.release());
	} else if (pValue->IsNil()) {
		DeleteTag(pSymbol);
	} else if (!pTag->AssignValue(pValue.release())) {
		return false;
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
