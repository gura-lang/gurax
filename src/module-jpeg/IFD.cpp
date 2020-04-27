//==============================================================================
// IFD.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// IFD
//------------------------------------------------------------------------------
bool IFD::WriteToBinary(Binary& buff, bool beFlag)
{
	SerialBuff serialBuff;
	size_t offsetToData = buff.size() + GetTagOwner().size() * sizeof(TypeDef_BE::TagPacked);
	for (Tag* pTag : GetTagOwner()) {
		if (!pTag->IsIFD()) {
			if (!pTag->SerializePre(serialBuff, offsetToData, beFlag)) return false;
		}
	}
	for (Tag* pTag : GetTagOwner()) {
		if (!pTag->Serialize(serialBuff, 0, beFlag)) return false;
	}
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
	return serialBuff.WriteToBinary(buff);
}

void IFD::PrepareTagMap()
{
	for (const Tag* pTag : GetTagOwner()) {
		_tagMap[pTag->GetSymbol()] = pTag->Reference();
	}
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
