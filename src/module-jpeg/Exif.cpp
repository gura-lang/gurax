//==============================================================================
// Exif.cpp
//==============================================================================
#include "stdafx.h"

Gurax_BeginModuleScope(jpeg)

//------------------------------------------------------------------------------
// Exif
//------------------------------------------------------------------------------
Value* Exif::CreateValue() const
{
	return new Value_Exif(Reference());
}

template<typename TypeDef> IFD* Exif::AnalyzeIFD(
	const Symbol* pSymbolOfIFD, const UInt8* buff, size_t bytesBuff, size_t offset, size_t* pOffsetNext)
{
	using IFDHeader_T	= typename TypeDef::IFDHeader;
	using LONG_T		= typename TypeDef::LONG;
	using Variable_T	= typename TypeDef::Variable;
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
		UInt32 count = Gurax_UnpackUInt32(tagPacked.count);
		const Variable_T& variable = tagPacked.variable;
		const TagInfo* pTagInfo = TagInfo::LookupByTagId(pSymbolOfIFD, tagId);
		//::printf("[%04x] %s type:%04x, count=%d\n",
		//		 tagId, (pTagInfo == nullptr)? "(unknown)" : pTagInfo->name, typeId, count);
		if (pTagInfo && pTagInfo->nameForIFD) {
			size_t offsetToValue = Gurax_UnpackUInt32(variable.LONG.num);
			const Symbol* pSymbolOfIFDSub = Symbol::Add(pTagInfo->nameForIFD);
			RefPtr<IFD> pIFD(AnalyzeIFD<TypeDef>(pSymbolOfIFDSub, buff, bytesBuff, offsetToValue));
			if (!pIFD) return nullptr;
			RefPtr<Tag> pTag(new Tag_IFD(tagId, count, pSymbolOfIFDSub, offset, offsetToValue, new Value_IFD(pIFD.release())));
			pTagOwner->push_back(pTag.release());
			continue;
		}
		const Symbol* pSymbol = pTagInfo? Symbol::Add(pTagInfo->name) : Symbol::Empty;
		RefPtr<Tag> pTag;
		switch (typeId) {
		case TypeId::BYTE: {
			pTag.reset((new Tag_BYTE(tagId, count, pSymbol, offset))->ReadFromBuff<TypeDef>(buff, bytesBuff, offset));
			if (!pTag) return nullptr;
			break;
		}
		case TypeId::ASCII: {
			pTag.reset((new Tag_ASCII(tagId, count, pSymbol, offset))->ReadFromBuff<TypeDef>(buff, bytesBuff, offset));
			if (!pTag) return nullptr;
			break;
		}
		case TypeId::SHORT: {
			pTag.reset((new Tag_SHORT(tagId, count, pSymbol, offset))->ReadFromBuff<TypeDef>(buff, bytesBuff, offset));
			if (!pTag) return nullptr;
			break;
		}
		case TypeId::LONG: {
			if (tagId == TagId::JPEGInterchangeFormat) {
				pTag.reset((new Tag_JPEGInterchangeFormat(tagId, count, pSymbol, offset))->
												ReadFromBuff<TypeDef>(buff, bytesBuff, offset));
			} else {
				pTag.reset((new Tag_LONG(tagId, count, pSymbol, offset))->ReadFromBuff<TypeDef>(buff, bytesBuff, offset));
			}
			if (!pTag) return nullptr;
			break;
		}
		case TypeId::RATIONAL: {
			pTag.reset((new Tag_RATIONAL(tagId, count, pSymbol, offset))->ReadFromBuff<TypeDef>(buff, bytesBuff, offset));
			if (!pTag) return nullptr;
			break;
		}
		case TypeId::UNDEFINED: {
			pTag.reset((new Tag_UNDEFINED(tagId, count, pSymbol, offset))->ReadFromBuff<TypeDef>(buff, bytesBuff, offset));
			if (!pTag) return nullptr;
			break;
		}
		case TypeId::SLONG: {
			pTag.reset((new Tag_SLONG(tagId, count, pSymbol, offset))->ReadFromBuff<TypeDef>(buff, bytesBuff, offset));
			if (!pTag) return nullptr;
			break;
		}
		case TypeId::SRATIONAL: {
			pTag.reset((new Tag_SRATIONAL(tagId, count, pSymbol, offset))->ReadFromBuff<TypeDef>(buff, bytesBuff, offset));
			if (!pTag) return nullptr;
			break;
		}
		default: {
			IssueError_InvalidFormat();
			return nullptr;
		}
		}
		pTagOwner->push_back(pTag.release());
	}
	if (pOffsetNext) {
		const LONG_T* pLONG = reinterpret_cast<const LONG_T*>(buff + offset);
		*pOffsetNext = Gurax_UnpackUInt32(pLONG->num);
	}
	return new IFD(pTagOwner.release());
}

bool Exif::AnalyzeBinary()
{
	//GetBinary()->Dump(Basement::Inst.GetStreamCOut());
	const UInt8* pBuff = GetBinary()->data();
	size_t bytesAvail = GetBinary()->size();
	do {
		if (bytesAvail < 6 || ::memcmp(pBuff, "Exif\0\0", 6) != 0) {
			IssueError_InvalidFormat();
			return false;
		}
		pBuff += 6, bytesAvail -= 6;
		if (bytesAvail < 2) {
			IssueError_InvalidFormat();
			return false;
		} else if (::memcmp(pBuff, "MM", 2) == 0) {
			size_t bytes = sizeof(TypeDef_BE::TIFFHeader);
			if (bytesAvail - 2 < bytes) {
				IssueError_InvalidFormat();
				return false;
			}
			auto& hdr = *reinterpret_cast<const TypeDef_BE::TIFFHeader*>(pBuff + 2);
			_beFlag = true;
			size_t offset = Gurax_UnpackUInt32(hdr.offset0thIFD);
			if (Gurax_UnpackUInt16(hdr.code) != 0x002a || bytesAvail < offset) {
				IssueError_InvalidFormat();
				return false;
			}
			for (int i = 0; i < 2 && offset != 0; i++) {
				RefPtr<IFD> pIFD(AnalyzeIFD<TypeDef_BE>(nullptr, pBuff, bytesAvail, offset, &offset));
				if (!pIFD) return false;
				_ifdOwner.push_back(pIFD.release());
			}
		} else if (::memcmp(pBuff, "II", 2) == 0) {
			size_t bytes = sizeof(TypeDef_LE::TIFFHeader);
			if (bytesAvail - 2 < bytes) {
				IssueError_InvalidFormat();
				return false;
			}
			auto& hdr = *reinterpret_cast<const TypeDef_LE::TIFFHeader*>(pBuff + 2);
			size_t offset = Gurax_UnpackUInt32(hdr.offset0thIFD);
			if (Gurax_UnpackUInt16(hdr.code) != 0x002a || bytesAvail < offset) {
				IssueError_InvalidFormat();
				return false;
			}
			for (int i = 0; i < 2 && offset != 0; i++) {
				RefPtr<IFD> pIFD(AnalyzeIFD<TypeDef_LE>(nullptr, pBuff, bytesAvail, offset, &offset));
				if (!pIFD) return false;
				_ifdOwner.push_back(pIFD.release());
			}
		} else {
			IssueError_InvalidFormat();
			return false;
		}
	} while (0);
	return true;
}

bool Exif::WriteToStream(Stream& stream)
{
	return UpdateBinary() && Segment::WriteToStream(stream);
}

bool Exif::UpdateBinary()
{
	RefPtr<BinaryReferable> pBuff(new BinaryReferable());
	Binary& buff = pBuff->GetBinary();
	buff.Append("Exif\0\0", 6);
	const UInt32 offset0thIFD = 2 + sizeof(TypeDef_BE::TIFFHeader);
	if (_beFlag) {
		buff.Append("MM", 2);
		TypeDef_BE::TIFFHeader hdr;
		Gurax_PackUInt16(hdr.code, 0x002a);
		Gurax_PackUInt32(hdr.offset0thIFD, offset0thIFD);
		buff.Append(&hdr, sizeof(hdr));
	} else {
		buff.Append("II", 2);
		TypeDef_LE::TIFFHeader hdr;
		Gurax_PackUInt16(hdr.code, 0x002a);
		Gurax_PackUInt32(hdr.offset0thIFD, offset0thIFD);
		buff.Append(&hdr, sizeof(hdr));
	}
	IFD* pIFDPrev = nullptr;
	for (IFD* pIFD : GetIFDOwner()) {
		if (!pIFDPrev) {
			// nothing to do
		} else if (_beFlag) {
			Tag::ReplaceLONG<TypeDef_BE>(buff, pIFDPrev->GetPosNextIFDOffset(), Tag::CalcOffset(buff));
		} else {
			Tag::ReplaceLONG<TypeDef_LE>(buff, pIFDPrev->GetPosNextIFDOffset(), Tag::CalcOffset(buff));
		}
		if (!pIFD->Serialize(buff, _beFlag)) return false;
		pIFDPrev = pIFD;
	}
	_pBuff.reset(pBuff.release());
	return true;
}

String Exif::ToString(const StringStyle& ss) const
{
	return "jpeg.Exif";
}

Gurax_EndModuleScope(jpeg)
