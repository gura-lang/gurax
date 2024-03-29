﻿//==============================================================================
// test-Stream.cpp
//==============================================================================
#include "stdafx.h"

namespace Gurax {

template<typename T_Num> void PrintNumList(const char* format, NumList<T_Num>& numList)
{
	auto pNum = numList.begin();
	if (pNum != numList.end()) {
		::printf(format, *pNum);
		pNum++;
		for ( ; pNum != numList.end(); pNum++) {
			::printf(", ");
			::printf(format, *pNum);
		}
	}
	::printf("\n");
}

void PrintBinary(const void* buff, size_t len)
{
	const UInt8* pBuff = reinterpret_cast<const UInt8*>(buff);
	if (len > 0) {
		::printf("0x%02x", *pBuff);
		pBuff++;
		len--;
		for ( ; len > 0; pBuff++, len--) {
			::printf(", 0x%02x", *pBuff);
		}
	}
	::printf("\n");
}

Gurax_TesterEntry(Stream)
{
	const char *str = "Gura";
	int n = 123456;
	Stream::COut->Printf("Hello %s World %d\n", str, n);
	RefPtr<ValueOwner> pValueOwner(new ValueOwner());
	pValueOwner->push_back(new Value_String(str));
	pValueOwner->push_back(new Value_Number(n));
	Stream::COut->PrintValueList("Hello %s World %d\n", *pValueOwner);
	do {
		using T_Num = UInt8;
		::printf("Serialize/Deserialize UInt8\n");
		static const T_Num numTbl[] = {
			0x00, 0x7f, 0x80, 0xff,
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(numTbl); i++) {
			RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
			pStream->SerializeNumber<T_Num>(numTbl[i]);
			::printf("0x%x: ", numTbl[i]);
			Stream::COut->Dump(pStream->GetBuff());
			pStream->Seek(0, Stream::SeekMode::Set);
			T_Num numDec;
			pStream->DeserializeNumber<T_Num>(numDec);
			::printf("  -> 0x%x\n", numDec);
		}
	} while (0);
	do {
		using T_Num = UInt16;
		::printf("Serialize/Deserialize UInt16\n");
		static const T_Num numTbl[] = {
			0x00, 0x7f, 0x80, 0xff,
			0x100, 0x1000, 0x7fff, 0x8000, 0xffff,
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(numTbl); i++) {
			RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
			pStream->SerializeNumber<T_Num>(numTbl[i]);
			::printf("0x%x: ", numTbl[i]);
			Stream::COut->Dump(pStream->GetBuff());
			pStream->Seek(0, Stream::SeekMode::Set);
			T_Num numDec;
			pStream->DeserializeNumber<T_Num>(numDec);
			::printf("  -> 0x%x\n", numDec);
		}
	} while (0);
	do {
		using T_Num = UInt32;
		::printf("Serialize/Deserialize UInt32\n");
		static const T_Num numTbl[] = {
			0x00, 0x7f, 0x80, 0xff,
			0x100, 0x1000, 0x7fff, 0x8000, 0xffff,
			0x00100000, 0x10000000, 0x7fffffff, 0x80000000, 0xffffffff,
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(numTbl); i++) {
			RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
			pStream->SerializeNumber<T_Num>(numTbl[i]);
			::printf("0x%x: ", numTbl[i]);
			Stream::COut->Dump(pStream->GetBuff());
			pStream->Seek(0, Stream::SeekMode::Set);
			T_Num numDec;
			pStream->DeserializeNumber<T_Num>(numDec);
			::printf("  -> 0x%x\n", numDec);
		}
	} while (0);
	do {
		using T_Num = Float;
		::printf("Serialize/Deserialize Float\n");
		static const T_Num numTbl[] = {
			0.f, 1.f, -1.f, 3.141f, -3.141f
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(numTbl); i++) {
			RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
			pStream->SerializeNumber<T_Num>(numTbl[i]);
			::printf("%.3f: ", numTbl[i]);
			Stream::COut->Dump(pStream->GetBuff());
			pStream->Seek(0, Stream::SeekMode::Set);
			T_Num numDec;
			pStream->DeserializeNumber<T_Num>(numDec);
			::printf("  -> %.3f\n", numDec);
		}
	} while (0);
	do {
		using T_Num = Double;
		::printf("Serialize/Deserialize Double\n");
		static const T_Num numTbl[] = {
			0, 1, -1, 3.141, -3.141
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(numTbl); i++) {
			RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
			pStream->SerializeNumber<T_Num>(numTbl[i]);
			::printf("%.3f: ", numTbl[i]);
			Stream::COut->Dump(pStream->GetBuff());
			pStream->Seek(0, Stream::SeekMode::Set);
			T_Num numDec;
			pStream->DeserializeNumber<T_Num>(numDec);
			::printf("  -> %.3f\n", numDec);
		}
	} while (0);
	do {
		using T_Num = UInt32;
		::printf("Serialize/Deserialize packed UInt32\n");
		static const T_Num numTbl[] = {
			0x00, 0x7f, 0x80, 0x3fff, 0x4000, 0x1fffff, 0x200000, 0xfffffff, 0x10000000, 0xffffffff,
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(numTbl); i++) {
			RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
			pStream->SerializePackedNumber<T_Num>(numTbl[i]);
			::printf("0x%x: ", numTbl[i]);
			Stream::COut->Dump(pStream->GetBuff());
			pStream->Seek(0, Stream::SeekMode::Set);
			T_Num numDec;
			pStream->DeserializePackedNumber<T_Num>(numDec);
			::printf("  -> 0x%x\n", numDec);
		}
	} while (0);
	do {
		using T_Num = UInt64;
		::printf("Serialize/Deserialize packed UInt64\n");
		static const T_Num numTbl[] = {
			0x00, 0x7f, 0x80, 0x3fff, 0x4000, 0x1fffff, 0x200000, 0xfffffff, 0x10000000, 0xffffffff,
			0x7ffffffffLL, 0x800000000LL,
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(numTbl); i++) {
			RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
			pStream->SerializePackedNumber<T_Num>(numTbl[i]);
			::printf("%zx: ", numTbl[i]);
			Stream::COut->Dump(pStream->GetBuff());
			pStream->Seek(0, Stream::SeekMode::Set);
			T_Num numDec;
			pStream->DeserializePackedNumber<T_Num>(numDec);
			::printf("  -> %zx\n", numDec);
		}
	} while (0);
	do {
		::printf("Serialize/Deserialize String\n");
		static const char* strTbl[] = {
			"", "A", "AB", "ABC", "A quick brown fox jumps over the lazy dog",
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(strTbl); i++) {
			RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
			pStream->SerializeString(strTbl[i]);
			::printf("\"%s\": ", strTbl[i]);
			Stream::COut->Dump(pStream->GetBuff());
			pStream->Seek(0, Stream::SeekMode::Set);
			String strDec;
			pStream->DeserializeString(strDec);
			::printf("  -> \"%s\"\n", strDec.c_str());
		}
	} while (0);
	do {
		::printf("Serialize/Deserialize Binary\n");
		static const char* strTbl[] = {
			"", "A", "AB", "ABC", "A quick brown fox jumps over the lazy dog",
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(strTbl); i++) {
			RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
			size_t len = ::strlen(strTbl[i]);
			pStream->SerializeBinary(Binary(strTbl[i], len));
			PrintBinary(strTbl[i], len);
			Stream::COut->Dump(pStream->GetBuff());
			pStream->Seek(0, Stream::SeekMode::Set);
			Binary binaryDec;
			pStream->DeserializeBinary(binaryDec);
			::printf("  -> ");
			PrintBinary(binaryDec.data(), binaryDec.size());
		}
	} while (0);
	do {
		::printf("Serialize/Deserialize Memory\n");
		static const char* strTbl[] = {
			"", "A", "AB", "ABC", "A quick brown fox jumps over the lazy dog",
		};
		for (size_t i = 0; i < Gurax_ArraySizeOf(strTbl); i++) {
			RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
			size_t len = ::strlen(strTbl[i]);
			RefPtr<Memory> pMemory(new MemoryHeap(len));
			::memcpy(pMemory->GetPointerC<void>(), strTbl[i], len);
			//pStream->SerializeMemory(*pMemory);
			pMemory->Serialize(*pStream);
			PrintBinary(pMemory->GetPointerC<void>(), len);
			Stream::COut->Dump(pStream->GetBuff());
			pStream->Seek(0, Stream::SeekMode::Set);
			RefPtr<Memory> pMemoryDec(Memory::Deserialize(*pStream));
			//pStream->DeserializeMemory(pMemoryDec);
			::printf("  -> ");
			PrintBinary(pMemory->GetPointerC<void>(), pMemory->GetBytes());
		}
	} while (0);
	do {
		using T_Num = UInt32;
		::printf("Serialize/Deserialize UInt32 List\n");
		NumList<T_Num> numList {
			0x00, 0x7f, 0x80, 0xff,
			0x100, 0x1000, 0x7fff, 0x8000, 0xffff,
			0x00100000, 0x10000000, 0x7fffffff, 0x80000000, 0xffffffff,
		};
		RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
		pStream->SerializeNumList<T_Num>(numList);
		PrintNumList<T_Num>("0x%x", numList);
		Stream::COut->Dump(pStream->GetBuff());
		pStream->Seek(0, Stream::SeekMode::Set);
		NumList<T_Num> numListDec;
		pStream->DeserializeNumList<T_Num>(numListDec);
		::printf("  -> ");
		PrintNumList<T_Num>("0x%x", numListDec);
	} while (0);
	do {
		using T_Num = UInt64;
		::printf("Serialize/Deserialize UInt64 List\n");
		NumList<T_Num> numList {
			0x00, 0x7f, 0x80, 0x3fff, 0x4000, 0x1fffff, 0x200000, 0xfffffff, 0x10000000, 0xffffffff,
			0x7ffffffffLL, 0x800000000LL,
		};
		RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
		pStream->SerializeNumList<T_Num>(numList);
		PrintNumList<T_Num>("0x%llx", numList);
		Stream::COut->Dump(pStream->GetBuff());
		pStream->Seek(0, Stream::SeekMode::Set);
		NumList<T_Num> numListDec;
		pStream->DeserializeNumList<T_Num>(numListDec);
		::printf("  -> ");
		PrintNumList<T_Num>("0x%llx", numListDec);
	} while (0);
	do {
		using T_Num = UInt32;
		::printf("Serialize/Deserialize Packed UInt32 List\n");
		NumList<T_Num> numList {
			0x00, 0x7f, 0x80, 0xff,
			0x100, 0x1000, 0x7fff, 0x8000, 0xffff,
			0x00100000, 0x10000000, 0x7fffffff, 0x80000000, 0xffffffff,
		};
		RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
		pStream->SerializePackedNumList<T_Num>(numList);
		PrintNumList<T_Num>("0x%x", numList);
		Stream::COut->Dump(pStream->GetBuff());
		pStream->Seek(0, Stream::SeekMode::Set);
		NumList<T_Num> numListDec;
		pStream->DeserializePackedNumList<T_Num>(numListDec);
		::printf("  -> ");
		PrintNumList<T_Num>("0x%x", numListDec);
	} while (0);
	do {
		using T_Num = UInt64;
		::printf("Serialize/Deserialize Packed UInt64 List\n");
		NumList<T_Num> numList {
			0x00, 0x7f, 0x80, 0x3fff, 0x4000, 0x1fffff, 0x200000, 0xfffffff, 0x10000000, 0xffffffff,
			0x7ffffffffLL, 0x800000000LL,
		};
		RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
		pStream->SerializePackedNumList<T_Num>(numList);
		PrintNumList<T_Num>("0x%llx", numList);
		Stream::COut->Dump(pStream->GetBuff());
		pStream->Seek(0, Stream::SeekMode::Set);
		NumList<T_Num> numListDec;
		pStream->DeserializePackedNumList<T_Num>(numListDec);
		::printf("  -> ");
		PrintNumList<T_Num>("0x%llx", numListDec);
	} while (0);
	do {
		::printf("Serialize/Deserialize Array\n");
		RefPtr<Array> pArray(Array::Create(Array::ElemType::Float, DimSizes::Create(3, 4, 5, 6)));
		Float* pElem = pArray->GetPointerC<Float>();
		for (size_t i = 0; i < pArray->GetDimSizes().CalcLength(); i++) *pElem++ = i;
		RefPtr<Stream_Binary> pStream(new Stream_Binary(Stream::Flag::Readable | Stream::Flag::Writable));
		pArray->Serialize(*pStream);
		::printf("%s\n", pArray->ToString().c_str());
		Stream::COut->Dump(pStream->GetBuff());
		pStream->Seek(0, Stream::SeekMode::Set);
		RefPtr<Array> pArrayDec(Array::Deserialize(*pStream));
		::printf("  -> %s\n", pArrayDec->ToString().c_str());
	} while (0);
}

}
