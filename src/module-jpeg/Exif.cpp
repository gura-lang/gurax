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

template<typename TypeDef> IFD* Exif::AnalyzeIFD(const UInt8* buff, size_t bytesBuff, size_t offset)
{
	using T_IFDHeader	= typename TypeDef::IFDHeader;
	using T_RATIONAL	= typename TypeDef::RATIONAL;
	using T_SRATIONAL	= typename TypeDef::SRATIONAL;
	using T_SHORT		= typename TypeDef::SHORT;
	using T_LONG		= typename TypeDef::LONG;
	using T_SLONG		= typename TypeDef::SLONG;
	using T_Variable	= typename TypeDef::Variable;
	using T_Tag			= typename TypeDef::Tag;
	if (offset + sizeof(T_IFDHeader) > bytesBuff) {
		IssueError_InvalidFormat();
		return nullptr;
	}
	RefPtr<IFD> pIFD(new IFD());
	auto& hdr = *reinterpret_cast<const T_IFDHeader*>(buff + offset);
	size_t tagCount = Gurax_UnpackUInt16(hdr.tagCount);
	offset += sizeof(T_IFDHeader);
	::printf("%zu\n", tagCount);
	if (offset + sizeof(T_Tag) * tagCount > bytesBuff) {
		IssueError_InvalidFormat();
		return nullptr;
	}
	for (size_t iTag = 0; iTag < tagCount; iTag++) {
		auto &tag = *reinterpret_cast<const T_Tag*>(buff + offset);
		offset += sizeof(T_Tag);
		UInt16 tagId = Gurax_UnpackUInt16(tag.tagId);
		UInt16 typeId = Gurax_UnpackUInt16(tag.typeId);
		UInt32 count = Gurax_UnpackUInt32(tag.count);
		const T_Variable& variable = tag.variable;
		switch (typeId) {
		case TypeId::BYTE: {
			const UInt8* p = variable.BYTE;
			if (count > 4) {
				size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
				if (offset + count * sizeof(UInt8) > bytesBuff) {
					IssueError_InvalidFormat();
					return nullptr;
				}
				p = buff + offset;
			}
			
			break;
		}
		case TypeId::ASCII: {
			const char* p = variable.ASCII;
			if (count > 4) {
				size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
				if (offset + count * sizeof(char) > bytesBuff) {
					IssueError_InvalidFormat();
					return nullptr;
				}
				p = reinterpret_cast<const char*>(buff + offset);
			}
			
			break;
		}
		case TypeId::SHORT: {
			if (count == 1) {
				UInt16 num = Gurax_UnpackUInt16(variable.SHORT.num);
			} else if (count == 2) {
				UInt16 num1 = Gurax_UnpackUInt16(variable.SHORT.num);
				UInt16 num2 = Gurax_UnpackUInt16(variable.SHORT.num2nd);
			} else {
				size_t offset = Gurax_UnpackUInt32(variable.LONG.num);
				if (offset + count * sizeof(UInt16) > bytesBuff) {
					IssueError_InvalidFormat();
					return nullptr;
				}
				
			}
			break;
		}
		case TypeId::LONG: {
			break;
		}
		case TypeId::RATIONAL: {
			break;
		}
		case TypeId::SLONG: {
			break;
		}
		case TypeId::SRATIONAL: {
			break;
		}
		default: {
			IssueError_InvalidFormat();
			return nullptr;
		}
		}
	}
#if 0
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
	return pIFD.release();
}

bool Exif::AnalyzeBinary()
{
	GetBinary()->Dump(Basement::Inst.GetStreamCOut());
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
			_bigEndianFlag = true;
			size_t offset = Gurax_UnpackUInt32(hdr.offset0thIFD);
			if (Gurax_UnpackUInt16(hdr.code) != 0x002a || bytesAvail < offset) {
				IssueError_InvalidFormat();
				return false;
			}
			RefPtr<IFD> pIFD(AnalyzeIFD<TypeDef_BE>(pBuff, bytesAvail, offset));
			if (!pIFD) return false;
			_ifdOwner.push_back(pIFD.release());
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
			RefPtr<IFD> pIFD(AnalyzeIFD<TypeDef_LE>(pBuff, bytesAvail, offset));
			if (!pIFD) return false;
			_ifdOwner.push_back(pIFD.release());
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
