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
	return true;
}

#if 0
bool IFD::WriteToBinary(Binary& buff, bool beFlag)
{
	SerialBuff serialBuff;
	size_t offsetToData = buff.size() +
					GetTagOwner().size() * sizeof(TypeDef_BE::TagPacked);
	UInt16 tagCount = static_cast<UInt16>(GetTagOwner().size());
	UInt32 offsetNextIFD = 0;
	if (beFlag) {
		TypeDef_BE::IFDHeader hdr;
		Gurax_PackUInt16(hdr.tagCount, tagCount);
		serialBuff.GetBuff().Append(&hdr, sizeof(hdr));
	} else {
		TypeDef_LE::IFDHeader hdr;
		Gurax_PackUInt16(hdr.tagCount, tagCount);
		serialBuff.GetBuff().Append(&hdr, sizeof(hdr));
	}
	for (Tag* pTag : GetTagOwner()) {
		if (!pTag->SerializePre(serialBuff, offsetToData, beFlag)) return false;
	}
	for (Tag* pTag : GetTagOwner()) {
		if (!pTag->Serialize(serialBuff, beFlag)) return false;
	}
	do {
		if (beFlag) {
			TypeDef_BE::LONG packed;
			Gurax_PackUInt32(packed.num, offsetNextIFD);
			serialBuff.GetBuff().Append(&packed, sizeof(packed));
		} else {
			TypeDef_LE::LONG packed;
			Gurax_PackUInt32(packed.num, offsetNextIFD);
			serialBuff.GetBuff().Append(&packed, sizeof(packed));
		}
	} while (0);
	return serialBuff.WriteToBinary(buff);
}
#endif

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
