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

template<typename T> IFD* Exif::AnalyzeIFD(const UInt8* pBuff, size_t bytesAvail)
{
#if 0
	if (offset + SIZE_IFDHeader >= bytesAPP1 - 1) {
		SetError_InvalidFormat(sig);
		return nullptr;
	}
	IFDHeader_T *pIFDHeader = reinterpret_cast<IFDHeader_T *>(buff + offset);
	size_t nTags = Gura_UnpackUInt16(pIFDHeader->TagCount);
	offset += SIZE_IFDHeader;
	if (offset + nTags * SIZE_TagRaw >= bytesAPP1 - 1) {
		SetError_InvalidFormat(sig);
		return nullptr;
	}
	if (pOffsetNext == nullptr) {
		// nothing to do
	} else if (offset + nTags * SIZE_TagRaw + UNITSIZE_LONG <= bytesAPP1) {
		LONG_T *pLong = reinterpret_cast<LONG_T *>(buff + offset + nTags * SIZE_TagRaw);
		*pOffsetNext = Gura_UnpackUInt32(pLong->num);
	} else {
		*pOffsetNext = 0;
	}
	AutoPtr<Object_ifd> pObjIFD(new Object_ifd(pSymbolOfIFD));
	for (size_t iTag = 0; iTag < nTags; iTag++, offset += SIZE_TagRaw) {
		TagRaw_T *pTagRaw = reinterpret_cast<TagRaw_T *>(buff + offset);
		unsigned short tagId = Gura_UnpackUInt16(pTagRaw->Id);
		unsigned short type = Gura_UnpackUInt16(pTagRaw->Type);
		unsigned long count = Gura_UnpackUInt32(pTagRaw->Count);
		ValueRaw_T *pValueRaw = reinterpret_cast<ValueRaw_T *>(&pTagRaw->ValueRaw);
		const TagInfo *pTagInfo = TagIdToInfo(pSymbolOfIFD, tagId);
#if 0
		do {
			const TypeInfo *pTypeInfo = TypeToInfo(type);
			::printf("%s [%04x], %s [%04x], %08x, %08x\n",
					(pTagInfo == nullptr)? "(unknown)" : pTagInfo->name, tagId,
					(pTypeInfo == nullptr)? "(unknown)" : pTypeInfo->name, type,
					count, Gura_UnpackUInt32(pValueRaw->LONG.num));
		} while (0);
#endif
		if (pTagInfo != nullptr && pTagInfo->nameForIFD != nullptr) {
			size_t offsetSub = Gura_UnpackUInt32(pValueRaw->LONG.num);
			size_t offsetNext = 0;
			const Symbol *pSymbolOfIFDSub = Symbol::Add(pTagInfo->nameForIFD);
			AutoPtr<Object_ifd> pObjIFDSub(ParseIFD_T<IFDHeader_T, TagRaw_T,
					ValueRaw_T, SHORT_T,
					LONG_T, RATIONAL_T, SLONG_T, SRATIONAL_T>(env, sig, pSymbolOfIFDSub,
									buff, bytesAPP1, offsetSub, &offsetNext));
			if (pObjIFDSub.IsNull()) return nullptr;
			const Symbol *pSymbol = Symbol::Add(pTagInfo->name);
			pObjIFD->GetTagOwner().push_back(new Object_tag(tagId, type, pSymbol, pObjIFDSub.release()));
		} else {
			Value value, valueCooked;
			switch (type) {
			case TYPE_BYTE: {
				char *p = pValueRaw->BYTE;
				if (count > 4) {
					size_t offset = Gura_UnpackUInt32(pValueRaw->LONG.num);
					if (offset + count >= bytesAPP1 - 1) {
						SetError_InvalidFormat(sig);
						return nullptr;
					}
					p = buff + offset;
				}
				value = Value(new Object_binary(env, p, count, false));
				valueCooked = value;
				break;
			}
			case TYPE_ASCII: {
				char *p = pValueRaw->ASCII;
				if (count > 4) {
					size_t offset = Gura_UnpackUInt32(pValueRaw->LONG.num);
					if (offset + count >= bytesAPP1 - 1) {
						SetError_InvalidFormat(sig);
						return nullptr;
					}
					p = buff + offset;
				}
				if (count == 0) {
					value = Value(p);
				} else {
					value = Value(p, count - 1);
				}
				valueCooked = value;
				break;
			}
			case TYPE_SHORT: {
				if (count == 1) {
					unsigned short num = Gura_UnpackUInt16(pValueRaw->SHORT.num);
					const Symbol *pSymbol = g_symbolAssocOwner.NumToSymbol(tagId, num);
					value = Value(num);
					if (pSymbol == nullptr) {
						valueCooked = value;
					} else {
						valueCooked = Value(pSymbol);
					}
				} else if (count == 2) {
					Object_list *pObjList = value.InitAsList(env);
					pObjList->Reserve(count);
					pObjList->Add(Value(Gura_UnpackUInt16(pValueRaw->SHORT.num)));
					pObjList->Add(Value(Gura_UnpackUInt16(pValueRaw->SHORT.second)));
					valueCooked = value;
				} else {
					Object_list *pObjList = value.InitAsList(env);
					pObjList->Reserve(count);
					size_t offset = Gura_UnpackUInt32(pValueRaw->LONG.num);
					if (offset + UNITSIZE_SHORT * count >= bytesAPP1 - 1) {
						SetError_InvalidFormat(sig);
						return nullptr;
					}
					for (unsigned int i = 0; i < count; i++, offset += UNITSIZE_SHORT) {
						SHORT_T *pShort = reinterpret_cast<SHORT_T *>(buff + offset);
						pObjList->Add(Value(Gura_UnpackUInt16(pShort->num)));
					}
					valueCooked = value;
				}
				break;
			}
			case TYPE_LONG: {
				if (count == 1) {
					value = Value(Gura_UnpackUInt32(pValueRaw->LONG.num));
				} else {
					Object_list *pObjList = value.InitAsList(env);
					pObjList->Reserve(count);
					size_t offset = Gura_UnpackUInt32(pValueRaw->LONG.num);
					if (offset + UNITSIZE_LONG * count >= bytesAPP1 - 1) {
						SetError_InvalidFormat(sig);
						return nullptr;
					}
					for (unsigned int i = 0; i < count; i++, offset += UNITSIZE_LONG) {
						LONG_T *pLong = reinterpret_cast<LONG_T *>(buff + offset);
						pObjList->Add(Value(Gura_UnpackUInt32(pLong->num)));
					}
				}
				valueCooked = value;
				break;
			}
			case TYPE_RATIONAL: {
				size_t offset = Gura_UnpackUInt32(pValueRaw->LONG.num);
				if (offset + UNITSIZE_RATIONAL * count >= bytesAPP1 - 1) {
					SetError_InvalidFormat(sig);
					return nullptr;
				}
				if (count == 1) {
					RATIONAL_T *pRational = reinterpret_cast<RATIONAL_T *>(buff + offset);
					value = RationalToValue(sig, *pRational);
					if (value.IsInvalid()) return nullptr;
				} else {
					Object_list *pObjList = value.InitAsList(env);
					pObjList->Reserve(count);
					size_t offset = Gura_UnpackUInt32(pValueRaw->LONG.num);
					if (offset + UNITSIZE_RATIONAL * count >= bytesAPP1 - 1) {
						SetError_InvalidFormat(sig);
						return nullptr;
					}
					for (unsigned int i = 0; i < count; i++, offset += UNITSIZE_RATIONAL) {
						RATIONAL_T *pRational = reinterpret_cast<RATIONAL_T *>(buff + offset);
						Value valueItem = RationalToValue(sig, *pRational);
						if (valueItem.IsInvalid()) return nullptr;
						pObjList->Add(valueItem);
					}
				}
				valueCooked = value;
				break;
			}
			case TYPE_UNDEFINED: {
				char *p = pValueRaw->BYTE;
				if (count > 4) {
					size_t offset = Gura_UnpackUInt32(pValueRaw->LONG.num);
					if (offset + count >= bytesAPP1 - 1) {
						SetError_InvalidFormat(sig);
						return nullptr;
					}
					p = buff + offset;
				}
				value = Value(new Object_binary(env, p, count, false));
				valueCooked = value;
				break;
			}
			case TYPE_SLONG: {
				if (count == 1) {
					value = Value(Gura_UnpackInt32(pValueRaw->SLONG.num));
				} else {
					Object_list *pObjList = value.InitAsList(env);
					pObjList->Reserve(count);
					size_t offset = Gura_UnpackInt32(pValueRaw->SLONG.num);
					if (offset + UNITSIZE_SLONG * count >= bytesAPP1 - 1) {
						SetError_InvalidFormat(sig);
						return nullptr;
					}
					for (unsigned int i = 0; i < count; i++, offset += UNITSIZE_SLONG) {
						SLONG_T *pLong = reinterpret_cast<SLONG_T *>(buff + offset);
						pObjList->Add(Value(Gura_UnpackUInt32(pLong->num)));
					}
				}
				valueCooked = value;
				break;
			}
			case TYPE_SRATIONAL: {
				size_t offset = Gura_UnpackUInt32(pValueRaw->LONG.num);
				if (offset + UNITSIZE_SRATIONAL * count >= bytesAPP1 - 1) {
					SetError_InvalidFormat(sig);
					return nullptr;
				}
				if (count == 1) {
					SRATIONAL_T *pRational = reinterpret_cast<SRATIONAL_T *>(buff + offset);
					value = SRationalToValue(sig, *pRational);
					if (value.IsInvalid()) return nullptr;
				} else {
					Object_list *pObjList = value.InitAsList(env);
					pObjList->Reserve(count);
					size_t offset = Gura_UnpackUInt32(pValueRaw->LONG.num);
					if (offset + UNITSIZE_SRATIONAL * count >= bytesAPP1 - 1) {
						SetError_InvalidFormat(sig);
						return nullptr;
					}
					for (unsigned int i = 0; i < count; i++, offset += UNITSIZE_SRATIONAL) {
						SRATIONAL_T *pRational = reinterpret_cast<SRATIONAL_T *>(buff + offset);
						Value valueItem = SRationalToValue(sig, *pRational);
						if (valueItem.IsInvalid()) return nullptr;
						pObjList->Add(valueItem);
					}
				}
				valueCooked = value;
				break;
			}
			default: {
				
				break;
			}
			}
			const Symbol *pSymbol = (pTagInfo == nullptr)?
								Symbol::Empty : Symbol::Add(pTagInfo->name);
			pObjIFD->GetTagOwner().push_back(new Object_tag(tagId, type, pSymbol, value, valueCooked));
		}
	}
	return pObjIFD.release();
#endif
	return nullptr;
}

bool Exif::AnalyzeBinary()
{
	GetBinary()->Dump(Basement::Inst.GetStreamCOut());
	const UInt8* pBuffTop = GetBinary()->data();
	const UInt8* pBuff = pBuffTop;
	size_t bytesAvail = GetBinary()->size();
	do {
		size_t bytes = sizeof(ExifHeader);
		if (bytesAvail < bytes) {
			IssueError_InvalidFormat();
			return false;
		}
		const ExifHeader& hdr = *reinterpret_cast<const ExifHeader*>(pBuff);
		pBuff += bytes, bytesAvail -= bytes;
		if (::memcmp(hdr.ByteOrder, "MM", 2) == 0) {
			size_t bytes = sizeof(TypeDef_BE::TIFFHeader);
			if (bytesAvail < bytes) {
				IssueError_InvalidFormat();
				return false;
			}
			auto& hdr = *reinterpret_cast<const TypeDef_BE::TIFFHeader*>(pBuff);
			//_bigEndianFlag = true;
			size_t offset = Gurax_UnpackUInt32(hdr.Offset0thIFD);
			if (Gurax_UnpackUInt16(hdr.Code) != 0x002a || bytesAvail < offset) {
				IssueError_InvalidFormat();
				return false;
			}
			RefPtr<IFD> pIFD(AnalyzeIFD<TypeDef_BE>(pBuffTop + offset, bytesAvail - offset));

		} else if (::memcmp(hdr.ByteOrder, "II", 2) == 0) {
			size_t bytes = sizeof(TypeDef_LE::TIFFHeader);
			if (bytesAvail < bytes) {
				IssueError_InvalidFormat();
				return false;
			}
			auto& hdr = *reinterpret_cast<const TypeDef_LE::TIFFHeader*>(pBuff);
			size_t offset = Gurax_UnpackUInt32(hdr.Offset0thIFD);
			if (Gurax_UnpackUInt16(hdr.Code) != 0x002a || bytesAvail < offset) {
				IssueError_InvalidFormat();
				return false;
			}
			RefPtr<IFD> pIFD(AnalyzeIFD<TypeDef_LE>(pBuffTop + offset, bytesAvail - offset));

		} else {
			IssueError_InvalidFormat();
			return false;
		}
	} while (0);

	return true;
}

bool Exif::Write(Stream& stream) const
{
	return Segment::Write(stream);
}

String Exif::ToString(const StringStyle& ss) const
{
	return "jpeg.Exif";
}

Gurax_EndModuleScope(jpeg)
